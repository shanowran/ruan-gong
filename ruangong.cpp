#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
#define NAMESIZE 20
#define MAX 1010
struct Activity {
	int num;
	char name[NAMESIZE];
	int day, extraDay, fee, fromNum, toNum;
	Activity() {}
	Activity(int _num, char _name[], int _day, int _extraDay, int _fee, int _fromNum, int _toNum) {
		num = _num;
		strcpy(name, _name);
		day = _day;
		extraDay = _extraDay;
		fee = _fee;
		fromNum = _fromNum;
		toNum = _toNum;
	}
};
typedef struct
{
	int a[100];
	int front;
	int rear;
}xin;
void create(xin& s)
{
	s.front = s.rear = 0;
}
void push(xin& s, int e)
{
	s.rear = (s.rear + 1) % 100;
	s.a[s.rear] = e;
}
void pop(xin& s, int& e)
{
	s.front = (s.front + 1) % 100;
	e = s.a[s.front];
}
int cd(xin& s)
{
	int lon;
	lon = (s.rear - s.front + 100) % 100;
	return lon;
}
vector<Activity>act;//活动 
void menu() {
	printf("*****************\n");
	printf("1 载入数据\n");
	printf("2 计算天数\n");
	printf("3 退出\n");
	printf("*****************\n");
	printf("请输入选项：");
}
void input() {//载入数据 
	act.clear();
	printf("请输入文件名：");
	char add[100] = { '\0' };
	scanf("%s", add);
	FILE* fp = NULL;
	fp = fopen(add, "r");
	if (fp != NULL) {
		while (!feof(fp)) {
			int num;
			char name[NAMESIZE];
			int day, extraDay, fee, fromNum, toNum;
			fscanf(fp, "%d %s %d %d %d %d %d", &num, name, &day, &extraDay, &fee, &fromNum, &toNum);
			act.push_back(Activity(num, name, day, extraDay, fee, fromNum, toNum));
		}
		fclose(fp);
		printf("载入成功\n");
	}
	else {
		printf("文件不存在\n");
	}
}
void cal() {//计算天数 
	int in[MAX] = { 0 }, maxNum = 0, time[MAX] = { 0 }, ans1 = 0, ans2 = 0, cost = 0;
	vector<pair<int, int> >e[MAX];
	bool pool[MAX] = { 0 };
	for (int i = 0; i < act.size(); ++i) {
		Activity& now = act[i];
		e[now.num].push_back(make_pair(now.toNum, now.day));
		in[now.toNum]++;
		maxNum = max(now.num, maxNum);
		if (!pool[now.num]) {
			cost += now.fee;
			pool[now.num] = 1;
		}
	}
	int q[MAX], front = 0, rear = 0;
	for (int i = 1; i <= maxNum; ++i) {
		if (in[i] == 0) {
			q[rear++] = i;
			rear %= MAX;
		}
	}
	while (rear != front) {
		int now = q[front++];
		for (int i = 0; i < e[now].size(); ++i) {
			int v = e[now][i].first, w = e[now][i].second;
			--in[v];
			time[v] = max(time[v], time[now] + w);
			if (in[v] == 0) {
				q[rear++] = v;
				rear %= MAX;
			}
		}
	}
	for (int i = 0; i <= maxNum; ++i) {
		ans1 = max(ans1, time[i]);//正常情况下的天数计算 
	}
	front = rear = 0;
	memset(time, 0, sizeof(time));
	for (int i = 1; i <= maxNum; ++i)e[i].clear();
	memset(in, 0, sizeof(in));
	for (int i = 0; i < act.size(); ++i) {
		Activity& now = act[i];
		e[now.num].push_back(make_pair(now.toNum, now.extraDay));
		in[now.toNum]++;
	}
	for (int i = 1; i <= maxNum; ++i) {
		if (in[i] == 0) {
			q[rear++] = i;
			rear %= MAX;
		}
	}
	while (rear != front) {
		int now = q[front++];
		for (int i = 0; i < e[now].size(); ++i) {
			int v = e[now][i].first, w = e[now][i].second;
			--in[v];
			time[v] = max(time[v], time[now] + w);
			if (in[v] == 0) {
				q[rear++] = v;
				rear %= MAX;
			}
		}
	}
	for (int i = 0; i <= maxNum; ++i) {
		ans2 = max(ans2, time[i]);//加班情况下的天数计算 
	}
	printf("正常情况下完成所需 %d 天\n", ans1);
	printf("加班情况下完成所需 %d 天 总加班费为：%d 元\n", ans2, cost);
}
int main() {
	menu();
	while (1) {
		char ch;
		ch = getchar();
		switch (ch) {
		case '1':input(); menu(); break;
		case '2':cal(); menu(); break;
		case '3':return 0; break;
		}
	}
	return 0;
}
