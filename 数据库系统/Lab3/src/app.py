import sys
import re

from data_manager.competition_manager import CompetitionManager, Level, STR2LEVEL
from data_manager.mysql_connect import MySQLConnect
from data_manager.participatein_manager import Category, Medal, ParticipateInManager, STR2MEDAL, STR2CATEGORY
from data_manager.school_manager import SchoolManager
from data_manager.player_manager import PlayerManager, Sex, Grade, STR2SEX, STR2GRADE
from data_manager.team_manager import TeamManager
from data_manager.membersof_manager import MembersOfManager, STR2ROLE
from PyQt5.QtGui import QStandardItem, QStandardItemModel
from PyQt5.QtWidgets import QApplication, QHeaderView, QInputDialog, QMainWindow, QMessageBox, QTableView
from ui.mainWindows import Ui_MainWindow


class App(QMainWindow, Ui_MainWindow):
    _SCHOOL_HEADER = ["ID", "名字", "国家", "省/州/自治区/特别行政区", "市", "注册队员数"]
    _PLAYER_HEADER = ["ID", "名字", "性别", "邮箱", "学校", "学院", "年级"]
    _TEAM_HEADER = ["ID", "名字", "学校"]
    _COMPETITION_HEADER = ["ID", "名字", "比赛日期", "比赛级别", "承办学校"]
    _PARTICIPATE_IN_HEADER = ["名次", "队伍", "奖牌", "类型"]
    __PARTICIPATE_IN_HEADER = ["队伍", "比赛", "名次", "奖牌", "队伍类型"]
    _TEAM_PLAYER_HEADER = ["ID", "名字", "性别", "邮箱", "学校", "学院", "年级", "队内角色"]

    def __init__(self, parent=None):
        super(App, self).__init__(parent)
        self.init_ui()
        self.init_action()
        self.init_manager()

    def init_ui(self):
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.tabWidget.setCurrentIndex(0)
        self.ui.tabWidget.setTabsClosable(False)

        self.ui.Competition_table.setEditTriggers(QTableView.NoEditTriggers)
        self.ui.Team_table.setEditTriggers(QTableView.NoEditTriggers)
        self.ui.Players_table.setEditTriggers(QTableView.NoEditTriggers)
        self.ui.Competition_table.setEditTriggers(QTableView.NoEditTriggers)

        model = QStandardItemModel()
        model.setHorizontalHeaderLabels(App._SCHOOL_HEADER)
        self.ui.School_table.setModel(model)
        self.ui.School_table.horizontalHeader().setSectionResizeMode(
            QHeaderView.ResizeToContents)

        model = QStandardItemModel()
        model.setHorizontalHeaderLabels(App._PLAYER_HEADER)
        self.ui.Players_table.setModel(model)
        self.ui.Players_table.horizontalHeader().setSectionResizeMode(
            QHeaderView.ResizeToContents)

        model = QStandardItemModel()
        model.setHorizontalHeaderLabels(App._TEAM_HEADER)
        self.ui.Team_table.setModel(model)
        self.ui.Team_table.horizontalHeader().setSectionResizeMode(
            QHeaderView.ResizeToContents)

        model = QStandardItemModel()
        model.setHorizontalHeaderLabels(App._COMPETITION_HEADER)
        self.ui.Competition_table.setModel(model)
        self.ui.Competition_table.horizontalHeader().setSectionResizeMode(
            QHeaderView.ResizeToContents)

    def init_action(self):
        self.ui.School_insert.clicked.connect(self.add_school)
        self.ui.School_List.clicked.connect(self.list_school)
        self.ui.School_search_Competitions.clicked.connect(self.search_competition_by_school)
        self.ui.School_search_Players.clicked.connect(self.search_player_by_school)
        self.ui.School_search_Teams.clicked.connect(self.search_team_by_school)
        self.ui.School_search.clicked.connect(self.search_school_by_keyword)

        self.ui.Players_insert.clicked.connect(self.add_player)
        self.ui.Players_list.clicked.connect(self.list_player)
        self.ui.Players_search.clicked.connect(self.search_player_by_keyword)
        self.ui.Players_info.clicked.connect(self.search_player_by_ID)
        self.ui.Players_participate_in.clicked.connect(self.search_player_participate_in)

        self.ui.Team_insert.clicked.connect(self.add_team)
        self.ui.Team_list.clicked.connect(self.list_team)
        self.ui.Team_search.clicked.connect(self.search_team_by_keyword)
        self.ui.Team_search_players.clicked.connect(self.search_player_by_Team)
        self.ui.Team_search_participate_in.clicked.connect(self.search_team_participate_in)

        self.ui.Competition_insert.clicked.connect(self.add_competition)
        self.ui.Competition_list.clicked.connect(self.list_competition)
        self.ui.Participate_in_insert.clicked.connect(self.add_participate_in)
        self.ui.Competition_result.clicked.connect(self.list_participate_in)
        self.ui.Competition_search.clicked.connect(self.search_competition_by_keyword)

    def init_manager(self):
        self.mysql_connect = MySQLConnect()
        self.school_manager = SchoolManager(self.mysql_connect)
        self.player_manager = PlayerManager(self.mysql_connect)
        self.team_manager = TeamManager(self.mysql_connect)
        self.members_of_manager = MembersOfManager(self.mysql_connect)
        self.competition_manager = CompetitionManager(self.mysql_connect)
        self.participate_in_manager = ParticipateInManager(self.mysql_connect)

    def add_school(self):
        name, ok = QInputDialog.getText(self, "输入学校全称", "输入学校全称")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        name = name.strip()
        if len(name) == 0:
            QMessageBox.critical(self, "错误", "学校名称不能为空")
            return

        nation, ok = QInputDialog.getText(self, "输入学校所在国家", "输入学校所在国家")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        nation = nation.strip()
        if len(nation) == 0:
            QMessageBox.critical(self, "错误", "学校国家不能为空")
            return

        province, ok = QInputDialog.getText(self, "输入学校所在省/州/自治区/特别行政区", "输入学校所在省/州/自治区/特别行政区")
        if not ok:
            QMessageBox.critical(self, "错误", "学校所在省/州/自治区/特别行政区不能为空")
            return
        province = province.strip()
        if len(province) == 0:
            QMessageBox.critical(self, "错误", "输入不能为空")
            return

        city, ok = QInputDialog.getText(self, "输入学校所在城市", "输入学校所在城市")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        city = city.strip()
        if len(city) == 0:
            QMessageBox.warning(self, "提示", "未输入学校所在城市")

        ok = self.school_manager.add_school(name, nation, province, city)
        if ok:
            QMessageBox.information(self, "提示", "添加成功！")
        else:
            QMessageBox.critical(self, "错误", "添加失败，请检查输入内容是否有误。")

    def list_school(self, items=0):
        if items == 0:
            items = self.school_manager.list_schools()
        self.ui.School_table.model().clear()
        self.ui.School_table.model().setHorizontalHeaderLabels(
            App._SCHOOL_HEADER)
        if items:
            for school in items:
                self.ui.School_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), school)))

    def search_competition_by_school(self):
        school, ok = QInputDialog.getText(self, "请输入学校名称", "请输入学校名称")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        school = school.strip()
        if school == "":
            QMessageBox.critical(self, "错误", "学校名称不能为空")
            return
        if self.school_manager.search_school_with_name(school) is None:
            QMessageBox.critical(self, "错误", "该学校不存在")
            return

        items = self.competition_manager.search_competition_with_school(school)
        self.ui.School_table.model().clear()
        self.ui.School_table.model().setHorizontalHeaderLabels(
            App._COMPETITION_HEADER)
        if items:
            for competition in items:
                self.ui.School_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), competition)))

    def search_player_by_school(self):
        school, ok = QInputDialog.getText(self, "请输入学校名称", "请输入学校名称")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        school = school.strip()
        if school == "":
            QMessageBox.critical(self, "错误", "学校名称不能为空")
            return
        if self.school_manager.search_school_with_name(school) is None:
            QMessageBox.critical(self, "错误", "该学校不存在")
            return

        items = self.player_manager.search_player_with_school(school)
        self.ui.School_table.model().clear()
        self.ui.School_table.model().setHorizontalHeaderLabels(
            App._PLAYER_HEADER)
        if items:
            for player in items:
                self.ui.School_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), player)))

    def search_team_by_school(self):
        school, ok = QInputDialog.getText(self, "请输入学校名称", "请输入学校名称")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        school = school.strip()
        if school == "":
            QMessageBox.critical(self, "错误", "学校名称不能为空")
            return
        if self.school_manager.search_school_with_name(school) is None:
            QMessageBox.critical(self, "错误", "该学校不存在")
            return

        items = self.team_manager.search_team_with_school(school)
        self.ui.School_table.model().clear()
        self.ui.School_table.model().setHorizontalHeaderLabels(
            App._TEAM_HEADER)
        if items:
            for team in items:
                self.ui.School_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), team)))

    def search_school_by_keyword(self):
        keyword, ok = QInputDialog.getText(self, "输入关键字", "输入关键字")
        if ok:
            items = self.school_manager.search_school_with_keyword(keyword)
            self.list_school(items)
        else:
            QMessageBox.critical(self, "错误", "无法获取输入内容")

    def add_player(self):
        name, ok = QInputDialog.getText(self, "输入选手姓名", "输入选手姓名")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        name = name.strip()
        if len(name) == 1:
            QMessageBox.critical(self, "错误", "请输入正确名字")
            return

        sex, ok = QInputDialog.getItem(
            self, "选择性别", "选择性别", map(lambda x: x.value, Sex))
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return

        e_mail, ok = QInputDialog.getText(self, "输入选手邮箱", "输入选手邮箱")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        e_mail = e_mail.strip()
        if e_mail.find("@") == -1:
            QMessageBox.critical(self, "错误", "请输入正确邮箱")
            return
        if self.player_manager.search_player_with_email(e_mail) is not None:
            QMessageBox.critical(self, "错误", "该邮箱已被注册")
            return

        school, ok = QInputDialog.getText(self, "输入选手所在学校全称", "输入选手所在学校全称")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        school = school.strip()
        if self.school_manager.search_school_with_name(school) is None:
            QMessageBox.critical(self, "错误", "无法找到该学校")
            return

        college, ok = QInputDialog.getText(self, "输入选手所在学院", "输入选手所在学院")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        college = college.strip()
        if college == "":
            QMessageBox.warning(self, "提示", "输入的学院名字为空")
            return

        grade, ok = QInputDialog.getItem(
            self, "选择年级", "选择年级", map(lambda x: x.value, Grade))
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        if not self.player_manager.add_player(
                name, STR2SEX[sex], e_mail, school, college, STR2GRADE[grade]):
            QMessageBox.critical(self, "错误", "无法添加")
            return
        else:
            QMessageBox.information(self, "提示", "添加成功")
            self.list_player()

    def list_player(self, items=0):
        if items == 0:
            items = self.player_manager.list_players()
        self.ui.Players_table.model().clear()
        self.ui.Players_table.model().setHorizontalHeaderLabels(
            App._PLAYER_HEADER)
        if items:
            for player in items:
                self.ui.Players_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), player)))

    def search_player_by_keyword(self):
        keyword, ok = QInputDialog.getText(self, "输入关键字", "输入关键字")
        if ok:
            items = self.player_manager.search_player_with_keyword(keyword)
            self.list_player(items)
        else:
            QMessageBox.critical(self, "错误", "无法获取输入内容")

    def search_player_by_ID(self):
        Id, ok = QInputDialog.getInt(self, "输入学号", "输入学号")
        if ok:
            items = self.player_manager.search_player_with_ID(Id)
            items = [items]
            self.list_player(items)
        else:
            QMessageBox.critical(self, "错误", "无法获取输入内容")

    def search_player_participate_in(self):
        Id, ok = QInputDialog.getInt(self, "输入学号", "输入学号")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
        items = self.participate_in_manager.search_player_participate_in(Id)
        self.ui.Players_table.model().clear()
        self.ui.Players_table.model().setHorizontalHeaderLabels(
            App.__PARTICIPATE_IN_HEADER)
        if items:
            for pti in items:
                self.ui.Players_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), pti)))

    def add_team(self):
        name, ok = QInputDialog.getText(self, "输入队伍名字", "输入队伍名字")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        name = name.strip()
        if name == "":
            QMessageBox.critical(self, "错误", "队伍名字不能为空")
            return
        if self.team_manager.search_team_with_name(name) is not None:
            QMessageBox.critical(self, "错误", "队伍名字已存在")
            return

        school, ok = QInputDialog.getText(self, "输入队伍所在学校", "输入队伍所在学校")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        school = school.strip()
        if school == "":
            QMessageBox.critical(self, "错误", "队伍所在学校名字不能为空")
            return
        if self.school_manager.search_school_with_name(school) is None:
            QMessageBox.critical(self, "错误", "该学校不存在")
            return

        coach_id, ok = QInputDialog.getInt(self, "输入教练ID", "输入教练ID")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        coach = self.player_manager.search_player_with_ID(coach_id)
        if coach is None or coach[4] != school:
            QMessageBox.critical(self, "错误", "该校未查到该教练")
            return
        if coach[6] != "教师":
            QMessageBox.critical(self, "错误", "这并不是一个教练")
            return

        captain_id, ok = QInputDialog.getInt(self, "输入队长ID", "输入队长ID")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        if captain_id == coach_id:
            QMessageBox.critical(self, "错误", "队长与教练不可是同一个人")
            return
        captain = self.player_manager.search_player_with_ID(captain_id)
        if captain is None or captain[4] != school:
            QMessageBox.critical(self, "错误", "该校未查到该选手")
            return
        if captain[6] == "教师":
            QMessageBox.critical(self, "错误", "这并不是一个学生")
            return

        member1_id, ok = QInputDialog.getInt(self, "输入队员一ID", "输入队员一ID")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        if member1_id == coach_id or member1_id == captain_id:
            QMessageBox.critical(self, "错误", "不可与其他队员或教练重复")
            return
        member1 = self.player_manager.search_player_with_ID(member1_id)
        if member1 is None or member1[4] != school:
            QMessageBox.critical(self, "错误", "该校未查到该选手")
            return
        if member1[6] == "教师":
            QMessageBox.critical(self, "错误", "这并不是一个学生")
            return

        member2_id, ok = QInputDialog.getInt(self, "输入队员二ID", "输入队员二ID")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        if member2_id == coach_id or member2_id == captain_id or member2_id == member1_id:
            QMessageBox.critical(self, "错误", "不可与其他队员或教练重复")
            return
        member2 = self.player_manager.search_player_with_ID(member2_id)
        if member2 is None or member2[4] != school:
            QMessageBox.critical(self, "错误", "该校未查到该选手")
            return
        if member2[6] == "教师":
            QMessageBox.critical(self, "错误", "这并不是一个学生")
            return

        if not self.team_manager.add_team(name, school):
            QMessageBox.critical(self, "错误", "无法添加")
            return
        else:
            QMessageBox.information(self, "提示", "添加成功")

        team_id = self.team_manager.search_team_with_name(name)
        team_id = team_id[0]
        print(team_id)
        self.members_of_manager.add_members_of(coach_id, name, STR2ROLE["教练"])
        self.members_of_manager.add_members_of(captain_id, name, STR2ROLE["队长"])
        self.members_of_manager.add_members_of(member1_id, name, STR2ROLE["队员"])
        self.members_of_manager.add_members_of(member2_id, name, STR2ROLE["队员"])
        self.list_team()

    def list_team(self, items=0):
        if items == 0:
            items = self.team_manager.list_teams()
        self.ui.Team_table.model().clear()
        self.ui.Team_table.model().setHorizontalHeaderLabels(
            App._TEAM_HEADER)
        if items:
            for team in items:
                self.ui.Team_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), team)))

    def search_team_by_keyword(self):
        keyword, ok = QInputDialog.getText(self, "输入关键字", "输入关键字")
        if ok:
            items = self.team_manager.search_team_with_keyword(keyword)
            self.list_team(items)
        else:
            QMessageBox.critical(self, "错误", "无法获取输入内容")

    def search_player_by_Team(self):
        team, ok = QInputDialog.getText(self, "输入队名", "输入队名")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")

        items = self.members_of_manager.search_members_of_players(team)
        self.ui.Team_table.model().clear()
        self.ui.Team_table.model().setHorizontalHeaderLabels(
            App._TEAM_PLAYER_HEADER)
        if items:
            for player in items:
                self.ui.Team_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), player)))

    def search_team_participate_in(self):
        team, ok = QInputDialog.getText(self, "输入队名", "输入队名")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
        items = self.participate_in_manager.search_participate_in_with_team(team)
        self.ui.Team_table.model().clear()
        self.ui.Team_table.model().setHorizontalHeaderLabels(
            App.__PARTICIPATE_IN_HEADER)
        if items:
            for pti in items:
                self.ui.Team_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), pti)))

    def add_competition(self):
        name, ok = QInputDialog.getText(self, "请输入比赛名称", "请输入比赛名称")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        name = name.strip()
        if name == "":
            QMessageBox.critical(self, "错误", "比赛名字不能为空")
            return
        if self.competition_manager.search_competition_with_name(name) is not None:
            QMessageBox.critical(self, "错误", "队伍名字已存在")
            return

        date, ok = QInputDialog.getText(self, "请输入比赛日期", "请输入比赛日期(yyyy-mm-dd)")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        date = date.strip()
        if date == "":
            QMessageBox.critical(self, "错误", "比赛日期不能为空")
            return
        if re.match(r"\d\d\d\d-\d\d-\d\d", date) is None:
            QMessageBox.critical(self, "错误", "请输入正确的日期格式（“yyyy-mm-dd”）")
            return

        level, ok = QInputDialog.getItem(
            self, "选择比赛级别", "选择比赛级别", map(lambda x: x.value, Level))
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return

        host, ok = QInputDialog.getText(self, "请输入承办学校", "请输承办学校")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        host = host.strip()
        if host == "":
            QMessageBox.critical(self, "错误", "承办学校不能为空")
            return
        if self.school_manager.search_school_with_name(host) is None:
            QMessageBox.critical(self, "错误", "未查到该学校")
            return

        if not self.competition_manager.add_competition(name, date, STR2LEVEL[level], host):
            QMessageBox.critical(self, "错误", "无法添加")
            return
        else:
            QMessageBox.information(self, "提示", "添加成功")
            self.list_competition()

    def list_competition(self, items=0):
        if items == 0:
            items = self.competition_manager.list_competition()
        self.ui.Competition_table.model().clear()
        self.ui.Competition_table.model().setHorizontalHeaderLabels(
            App._COMPETITION_HEADER)
        if items:
            for competition in items:
                self.ui.Competition_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), competition)))

    def search_competition_by_keyword(self):
        keyword, ok = QInputDialog.getText(self, "输入关键字", "输入关键字")
        if ok:
            items = self.competition_manager.search_competition_with_keyword(keyword)
            self.list_competition(items)
        else:
            QMessageBox.critical(self, "错误", "无法获取输入内容")

    def add_participate_in(self):

        competition, ok = QInputDialog.getText(self, "请输入比赛名称", "请输入比赛名称")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        competition = competition.strip()
        if competition == "":
            QMessageBox.critical(self, "错误", "比赛名称不能为空")
            return
        competition_info = self.competition_manager.search_competition_with_name(competition)
        if competition_info is None:
            QMessageBox.critical(self, "错误", "该比赛不存在")
            return

        team, ok = QInputDialog.getText(self, "请输入队伍名称", "请输入队伍名称")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        team = team.strip()
        if team == "":
            QMessageBox.critical(self, "错误", "队伍名字不能为空")
            return
        team_info = self.team_manager.search_team_with_name(team)
        if team_info is None:
            QMessageBox.critical(self, "错误", "该队伍不存在")
            return
        if self.team_manager.special_judge_players(team, competition) > 0:
            QMessageBox.critical(self, "错误", "该队伍队员与本场比赛其他队员重复")
            return

        category, ok = QInputDialog.getItem(
            self, "选择队伍类别", "选择队伍类别", map(lambda x: x.value, Category))
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return

        if category == "正式":
            medal, ok = QInputDialog.getItem(self, "选择奖牌", "选择奖牌", map(lambda x: x.value, Medal))
        else :
            medal, ok = QInputDialog.getItem(self, "选择奖牌", "选择奖牌", map(lambda x: x.value, Medal[3:4]))
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return

        place, ok = QInputDialog.getInt(self, "请输入名次", "请输入名次")
        if not ok:
            QMessageBox.critical(self, "错误", "无法获取输入内容")
            return
        if place <= 0:
            QMessageBox.critical(self, "错误", "名次须为正数")
            return

        if not self.participate_in_manager.add_participate_in(
                team, competition, STR2MEDAL[medal], place, STR2CATEGORY[category]):
            QMessageBox.critical(self, "错误", "无法添加")
            return
        else:
            QMessageBox.information(self, "提示", "添加成功")
        self.list_participate_in(competition)

    def list_participate_in(self, competition = 0):
        if competition == 0:
            competition, ok = QInputDialog.getText(self, "请输入比赛名称", "请输入比赛名称")
            if not ok:
                QMessageBox.critical(self, "错误", "无法获取输入内容")
                return
            competition = competition.strip()
            if competition == "":
                QMessageBox.critical(self, "错误", "比赛名称不能为空")
                return
            competition_info = self.competition_manager.search_competition_with_name(competition)
            if competition_info is None:
                QMessageBox.critical(self, "错误", "该比赛不存在")
                return

        items = self.participate_in_manager.list_participate_in(competition)
        self.ui.Competition_table.model().clear()
        self.ui.Competition_table.model().setHorizontalHeaderLabels(
            App._PARTICIPATE_IN_HEADER)
        if items:
            for participate_in in items:
                self.ui.Competition_table.model().appendRow(
                    list(map(lambda x: QStandardItem(str(x)), participate_in)))


if __name__ == '__main__':
    env = QApplication(sys.argv)
    app = App()
    app.show()
    sys.exit(env.exec_())
