import enum

from data_manager.mysql_connect import MySQLConnect


class Category(enum.Enum):
    OFFICIAL = "正式"
    UNOFFICIAL = "非正式"


class Medal(enum.Enum):
    GOLD = "金奖"
    SILVER = "银奖"
    BRONZE = "铜奖"
    HONOR = "优胜奖"


STR2CATEGORY = dict(map(lambda x: (x.value, x), Category))
STR2MEDAL = dict(map(lambda x: (x.value, x), Medal))


class ParticipateInManager:
    _SEARCH_RAW = """SELECT participate_in.Team, participate_in.Competition, 
     participate_in.Place, participate_in.Medal, participate_in.Category FROM participate_in """

    _SEARCH_RAW_SHOW = """SELECT participate_in.Place, participate_in.Team, participate_in.Medal,  participate_in.Category 
    FROM participate_in """

    def __init__(self, conn: MySQLConnect):
        self._conn = conn

    def add_participate_in(self, team: str, competition: str, medal: Medal, place: int, category: Category):
        return self._conn.add_tuple(
            "participate_in", "Team, Competition, Medal, Place, Category",
            ", ".join(map(repr, [team, competition, medal.value, place, category.value])))

    def list_participate_in(self, competition: str):
        return self._conn.query_all(ParticipateInManager._SEARCH_RAW_SHOW + "WHERE Competition = '{}';".format(competition))

    def search_participate_in_with_competition(self, competition: str):
        return self._conn.query_all(ParticipateInManager._SEARCH_RAW +
                                    " WHERE Competition = \"{}\";".format(competition))

    def search_participate_in_with_competition_official(self, competition: str):
        return self._conn.query_all(ParticipateInManager._SEARCH_RAW +
                                    " WHERE Competition = \"{}\" AND Category = \"{}\";".format(competition, "正式"))

    def search_participate_in_with_team(self, team: str):
        return self._conn.query_all(ParticipateInManager._SEARCH_RAW +
                                    " WHERE Team = \"{}\";".format(team))

    def search_player_participate_in(self, player: int):
        return self._conn.query_all(ParticipateInManager._SEARCH_RAW + """ WHERE Team 
            IN (SELECT Team FROM members_of WHERE Player = {}) ;""".format(player))