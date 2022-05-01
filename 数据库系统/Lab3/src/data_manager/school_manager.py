from data_manager.mysql_connect import MySQLConnect


class SchoolManager:
    _SEARCH_RAW = """SELECT school.Id, school.Name, school.Nation, school.Province,
            school.City, P.num FROM school INNER JOIN (SELECT school, count(*) FROM players GROUP BY school) 
            AS P(school, num) ON school.Name = P.School"""

    def __init__(self, conn: MySQLConnect):
        self._conn = conn

    def add_school(self, name: str, nation: str, province: str, city: str):
        if name == '' or nation == '' or province == '':
            return False
        return self._conn.add_tuple(
            "school", "Name, Nation, Province, City",
            ", ".join(map(repr, [name, nation, province, city])))

    def list_schools(self):
        return self._conn.query_all(SchoolManager._SEARCH_RAW + ";")

    def search_school_with_name(self, name: str):
        return self._conn.query_one(SchoolManager._SEARCH_RAW +
                                    " WHERE Name = \"{}\";".format(name))

    def search_school_with_keyword(self, keyword: str):
        return self._conn.query_all(SchoolManager._SEARCH_RAW +
                                    " WHERE school.Name LIKE '%{}%';".format(keyword))