from data_manager.MysqlConnect import MySQLConnect


class TeamManager:
    _SEARCH_RAW = """SELECT team.ID, team.Name, team.School FROM team """

    def __init__(self, conn: MySQLConnect):
        self._conn = conn

    def add_team(self, name: str, school: str):
        if name == '' or school == '':
            return False
        return self._conn.add_tuple(
            "team", "Name, School",
            ", ".join(map(repr, [name, school])))

    def search_team_with_name(self, name: str):
        return self._conn.query_one(TeamManager._SEARCH_RAW +
                                    " WHERE Name = \"{}\";".format(name))

    def search_team_with_school(self, school: str):
        return self._conn.query_all(TeamManager._SEARCH_RAW +
                                    " WHERE School = \"{}\";".format(school))

    def list_teams(self):
        return self._conn.query_all(TeamManager._SEARCH_RAW + ";")

    def search_team_with_keyword(self, keyword: str):
        return self._conn.query_all(TeamManager._SEARCH_RAW +
                                    " WHERE Name LIKE '%{}%';".format(keyword))

    def special_judge_players(self, team: str, competition: str):
        return self._conn.query_count("""SELECT * FROM (SELECT * FROM members_of WHERE Team in (SELECT Team FROM participate_in WHERE Competition = '{}'))
    AS P1 INNER JOIN (SELECT * FROM members_of WHERE Team = '{}' AND Role != '教练') AS P2 ON P1.Player = P2.Player ;""".format(competition, team))
