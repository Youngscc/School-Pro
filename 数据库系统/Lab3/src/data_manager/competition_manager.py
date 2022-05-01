import enum

from data_manager.mysql_connect import MySQLConnect


class Level(enum.Enum):
    INTERNATIONAL = "国际级"
    NATIONAL = "国家级"
    REGIONAL = "地区级"
    PROVINCIAL = "省级"
    MUNICIPAL = "市级"


STR2LEVEL = dict(map(lambda x: (x.value, x), Level))


class CompetitionManager:
    _SEARCH_RAW = """SELECT competition.ID, competition.Name, competition.Time, 
     competition.Level, competition.Host FROM competition """

    def __init__(self, conn: MySQLConnect):
        self._conn = conn

    def add_competition(self, name: str, time: str, level: Level, host: str):
        print(name, host)
        return self._conn.add_tuple(
            "competition", "Name, Time, Level, Host",
            ", ".join(map(repr, [name, time, level.value, host])))

    def list_competition(self):
        return self._conn.query_all(CompetitionManager._SEARCH_RAW + ";")

    def search_competition_with_name(self, name: str):
        return self._conn.query_one(CompetitionManager._SEARCH_RAW +
                                    " WHERE Name = \"{}\";".format(name))

    def search_competition_with_school(self, school: str):
        return self._conn.query_all(CompetitionManager._SEARCH_RAW +
                                    " WHERE Host = \"{}\";".format(school))

    def search_competition_with_keyword(self, keyword: str):
        return self._conn.query_all(CompetitionManager._SEARCH_RAW +
                                    " WHERE Name LIKE '%{}%';".format(keyword))