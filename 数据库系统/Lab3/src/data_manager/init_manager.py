import enum

from data_manager.mysql_connect import MySQLConnect
from data_manager.competition_manager import CompetitionManager, Level, STR2LEVEL
from data_manager.participatein_manager import Category, Medal, ParticipateInManager, STR2MEDAL, STR2CATEGORY
from data_manager.school_manager import SchoolManager
from data_manager.player_manager import PlayerManager, Sex, Grade, STR2SEX, STR2GRADE
from data_manager.team_manager import TeamManager
from data_manager.membersof_manager import MembersOfManager, STR2ROLE

mysql_connect = MySQLConnect()
school_manager = SchoolManager(mysql_connect)
player_manager = PlayerManager(mysql_connect)
team_manager = TeamManager(mysql_connect)
members_of_manager = MembersOfManager(mysql_connect)
competition_manager = CompetitionManager(mysql_connect)
participate_in_manager = ParticipateInManager(mysql_connect)


def init():
    mysql_connect.foreign_key_set(0)
    mysql_connect.clear_table("participate_in")
    mysql_connect.clear_table("members_of")
    mysql_connect.clear_table("competition")
    mysql_connect.clear_table("team")
    mysql_connect.clear_table("players")
    mysql_connect.clear_table("school")
    mysql_connect.foreign_key_set(1)


def init_school():
    for i in range(1, 20):
        province = "cn-P{}".format(i)
        for j in range(10):
            city = province + "-C{}".format(j)
            for k in range(10):
                school = city + "-U{}".format(k)
                school_manager.add_school(school, "中国", province, city)


def getGrade(p: int):
    if p == 0: return "大一"
    if p == 1: return "大二"
    if p == 2: return "大三"
    if p == 3: return "大四"
    if p == 4: return "大五"
    if p == 5: return "研一"
    if p == 6: return "研二"
    if p == 7: return "研三"


def init_players():
    p = 0
    for i in range(1, 20):
        province = "cn-P{}".format(i)
        for j in range(10):
            city = province + "-C{}".format(j)
            for k in range(10):
                school = city + "-U{}".format(k)
                player_manager.add_player(school + "-t", STR2SEX["男"], school + "@163.com", school, "计算机学院",
                                          STR2GRADE["教师"])
                for l in range(27):
                    player = school + "-p{}".format(l)
                    player_manager.add_player(player, STR2SEX["男"], player + "@163.com", school, "计算机学院",
                                              STR2GRADE[getGrade(p)])
                    p = p + 1
                    if p == 8:
                        p = 0


def init_team():
    for i in range(1, 20):
        province = "cn-P{}".format(i)
        for j in range(10):
            city = province + "-C{}".format(j)
            for k in range(10):
                school = city + "-U{}".format(k)
                for l in range(9):
                    team = school + "-T{}".format(l)
                    team_manager.add_team(team, school)
                    members_of_manager.add_members_of(player_manager.search_player_with_email(school + "@163.com")[0],
                                                      team, STR2ROLE["教练"])
                    members_of_manager.add_members_of(
                        player_manager.search_player_with_email(school + "-p{}".format(l * 3) + "@163.com")[0], team,
                        STR2ROLE["队长"])
                    members_of_manager.add_members_of(
                        player_manager.search_player_with_email(school + "-p{}".format(l * 3 + 1) + "@163.com")[0],
                        team, STR2ROLE["队员"])
                    members_of_manager.add_members_of(
                        player_manager.search_player_with_email(school + "-p{}".format(l * 3 + 2) + "@163.com")[0],
                        team, STR2ROLE["队员"])
                team = school + "-T"
                team_manager.add_team(team, school)
                members_of_manager.add_members_of(player_manager.search_player_with_email(school + "@163.com")[0],
                                                  team, STR2ROLE["教练"])
                members_of_manager.add_members_of(
                    player_manager.search_player_with_email(school + "-p{}".format(1) + "@163.com")[0], team,
                    STR2ROLE["队长"])
                members_of_manager.add_members_of(
                    player_manager.search_player_with_email(school + "-p{}".format(3) + "@163.com")[0],
                    team, STR2ROLE["队员"])
                members_of_manager.add_members_of(
                    player_manager.search_player_with_email(school + "-p{}".format(5) + "@163.com")[0],
                    team, STR2ROLE["队员"])


def init_competition():
    for u in range(3):
        host = "cn-P1-C0-U{}".format(u)
        for h in range(10):
            competition = "ICPC-{}{}".format(h,u)
            competition_manager.add_competition(competition, "2022-10-09", STR2LEVEL["国家级"], host)
            rk = 1
            for i in range(1, 20):
                province = "cn-P{}".format(i)
                for j in range(10):
                    city = province + "-C{}".format(j)
                    for k in range(10):
                        school = city + "-U{}".format(k)
                        team = school + "-T{}".format(h)
                        if rk <= 10:
                            medal = "金奖"
                        elif rk <= 50:
                            medal = "银奖"
                        elif rk <= 200:
                            medal = "铜奖"
                        else:
                            medal = "优胜奖"
                        participate_in_manager.add_participate_in(team, competition, STR2MEDAL[medal], rk,
                                                                  STR2CATEGORY["正式"])
                        rk = rk+1


if __name__ == '__main__':
    init()
    init_school()
    init_players()
    init_team()
    init_competition()
