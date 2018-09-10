from bs4 import BeautifulSoup

import getpass
import requests
import re
import os


def save(pid, code, language):
    counter = 0
    while True:
        raw = str(pid)
        if counter:
            raw += "-%d" % counter
        if language == "Java":
            filename = raw + ".java"
        else:
            filename = raw + ".cpp"
        if not os.path.exists(filename):
            with open(filename, "w") as f:
                f.write(code)
            print("Saved to", filename)
            break
        counter += 1


hostname = "http://acm.hdu.edu.cn"

contest = int(input("Contest ID? Type 0 to get codes from the problemset: "))
username = input("Username: ")
password = getpass.getpass("Password: ")

if contest:
    start_pid = int(input("Start of problem IDs in the problemset: "))
else:
    start_pid = 0

headers = {'user-agent': "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.98 Safari/537.36"}
session = requests.Session()
if contest:
    r = session.post(hostname + "/userloginex.php?action=login&cid=%d&notice=0" % contest, data={'username': username, 'userpass': password},
                     headers=headers)
    status_page = "/contests/contest_status.php?cid=%d&pid=&user=%s&lang=0&status=5" % (contest, username)
else:
    r = session.post(hostname + "/userloginex.php?action=login", data={'username': username, 'userpass': password},
                                                                 headers=headers)
    status_page = "/status.php?user=%s&pid=0&lang=0&status=5" % username


id_repo = set()

while True:
    page_content = session.get(hostname + status_page, headers=headers).content.decode(errors='ignore')
    if not contest:
        keys = ["id", "datetime", "status", "pid", "time", "memory", "code_length", "language", "user"]
    else:
        keys = ["id", "datetime", "status", "pid", "time", "memory", "language", "user"]

    ok = False

    for row_str in re.findall(r"(<tr\s*(bgcolor=\#D7EBFF)?\s*align=center\s*><td height=22(px)?>\d+</td>.*?</tr>)", page_content):
        row = BeautifulSoup(row_str[0], "html.parser")
        data = {}
        for i, x in enumerate(row.find_all("td")):
            data[keys[i]] = x.string
        code_page = data["id"]
        if contest:
            code_page = "/viewcode.php?rid=%s&cid=%d" % (data['id'], contest)
        else:
            code_page = "/viewcode.php?rid=" + data["id"]
        if data["id"] not in id_repo:
            ok = True

            code_page_content = session.get(hostname + code_page, headers=headers).content
            doc = BeautifulSoup(code_page_content, "html.parser")
            code_content = doc.find(id="usercode").string
            print(data)
            id_repo.add(data["id"])
            code_content = code_content.replace('\r\n', '\n')
            code_content = "// [Auto Archived]\n// Submit: %s\n// Time: %s\n// Memory: %s\n\n" % (data["datetime"], data["time"], data["memory"]) + code_content
            problem_id = int(data["pid"])
            if contest:
                problem_id = problem_id - 1001 + start_pid
            save(problem_id, code_content, data["language"])

    if not ok:
        break

    match = re.search(r"href=\"(((?!href).)*?)\">Next Page", page_content)
    if not match:
        break
    status_page = match.group(1)
    if not status_page.startswith("/"):
        status_page = "/contests/" + status_page
    print(status_page)
