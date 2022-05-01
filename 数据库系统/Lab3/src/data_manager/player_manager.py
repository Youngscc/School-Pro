import enum

from data_manager.mysql_connect import MySQLConnect


class Sex(enum.Enum):
    MALE = "男"
    FEMALE = "女"


class Grade(enum.Enum):
    FRESHMAN = "大一"
    SOPHOMORE = "大二"
    JUNIOR = "大三"
    SENIOR = "大四"
    FIFTH_GRADE = "大五"
    MASTER_ONE = "研一"
    MASTER_TWO = "研二"
    MASTER_THREE = "研三"
    TEACHER = "教师"


STR2SEX = dict(map(lambda x: (x.value, x), Sex))
STR2GRADE = dict(map(lambda x: (x.value, x), Grade))


class PlayerManager:
    _SEARCH_RAW = """SELECT players.ID, players.Name, players.Sex, players.E_mail,
     players.School, players.College, players.Grade FROM players """

    def __init__(self, conn: MySQLConnect):
        self._conn = conn

    def add_player(self, name: str, sex: Sex, e_mail: str, school: str, college: str, grade: Grade):
        if name == '' or e_mail == '' or college == '' or school == '':
            return False
        return self._conn.add_tuple(
            "players", "Name, Sex, E_mail, School, College, Grade",
            ", ".join(map(repr, [name, sex.value, e_mail, school, college, grade.value])))

    def list_players(self):
        return self._conn.query_all(PlayerManager._SEARCH_RAW + ";")

    def search_player_with_email(self, e_mail: str):
        return self._conn.query_one(PlayerManager._SEARCH_RAW +
                                    " WHERE E_mail = \"{}\";".format(e_mail))

    def search_player_with_school(self, school: str):
        return self._conn.query_all(PlayerManager._SEARCH_RAW +
                                    " WHERE School = \"{}\";".format(school))

    def search_player_with_ID(self, Id: int):
        return self._conn.query_one(PlayerManager._SEARCH_RAW +
                                    " WHERE ID = {};".format(Id))

    def search_player_with_keyword(self, keyword: str):
        return self._conn.query_all(PlayerManager._SEARCH_RAW +
                                    " WHERE Name LIKE '%{}%' OR E_mail LIKE '%{}%';".format(keyword, keyword))


