import enum

from data_manager.MysqlConnect import MySQLConnect


class Role(enum.Enum):
    COACH = "教练"
    CAPTAIN = "队长"
    MEMBER = "队员"


STR2ROLE = dict(map(lambda x: (x.value, x), Role))


class MembersOfManager:
    _SEARCH_RAW = """SELECT members_of.Player, 
    members_of.Team, members_of.Role FROM members_of """

    def __init__(self, conn: MySQLConnect):
        self._conn = conn

    def add_members_of(self, player: int, team: str, role: Role):
        return self._conn.add_tuple(
            "members_of", "Player, Team, Role",
            ", ".join(map(repr, [player, team, role.value])))

    def search_members_of_players(self, team: str):
        return self._conn.query_all(""" SELECT ID, Name, Sex, E_mail, School, College, Grade, Role 
        FROM (SELECT * FROM players WHERE ID IN (SELECT Player FROM members_of WHERE Team = '{}')) AS P1
    INNER JOIN (SELECT Player, Role FROM members_of WHERE Team = '{}') AS P2 ON P1.ID = P2.Player ;""".format(team,team))

