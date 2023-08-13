
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;
bool visited[20000];//访问结点的标志

typedef struct route
{
	string origin_city, destination_city, transport, other_information;
	float time, cost;
}Route, Arcs;


typedef struct city
{   //顶点
	bool pass = false;
	string country, city;
	float latitude, longitude;
}City, Vertex;


struct Graph {  //邻接矩阵
	Vertex* vertex;
	Arcs arcs[199][199];
	int vexnum, arcnum;
};

struct Way {
	int path;
	int pre;
};

void readGraphData(City* ct, Route* route) {
	/*cout << "打开文件开始" << endl;*/
	int i = 0, j = 0;  //循环变量
	//读取顶点(城市)数据文件
	FILE* fp = fopen("cities.csv", "r");
	if (!fp) {
		cout << "error1!";
		exit(0);
	}
	char ch;
	float f;
	while (!feof(fp)) {
		//依次读取，碰到逗号则跳入下一个
		ch = fgetc(fp);
		for (; ch != ','; ch = fgetc(fp)) {
			ct[i].country += ch;
		}
		/*cout << ct[i].country << ",";*/
		ch = fgetc(fp);    //抵消逗号
		for (; ch != ','; ch = fgetc(fp)) {
			ct[i].city += ch;
		}
		/*cout << ct[i].city << ",";*/
		fscanf(fp, "%f,", &f);
		ct[i].latitude = f;
		/*cout << ct[i].latitude << ",";*/
		fscanf(fp, "%f\n", &f);
		ct[i].longitude = f;
		/*cout << ct[i].longitude << endl;*/
		i++;
	}
	fclose(fp);

	//读取路径文件
	FILE* fp1 = fopen("routes.csv", "r");
	if (!fp1) {
		cout << "error2!";
		exit(0);
	}

	i = 0;
	ch = fgetc(fp1);
	while (!feof(fp1)) {
		//依次读取，碰到逗号则跳入下一个
		for (; ch != ','; ch = fgetc(fp1)) {
			route[i].origin_city += ch;
		}
		ch = fgetc(fp1);//抵消逗号
		for (; ch != ','; ch = fgetc(fp1)) {
			route[i].destination_city += ch;
		}
		ch = fgetc(fp1);//抵消逗号
		for (; ch != ','; ch = fgetc(fp1)) {
			route[i].transport += ch;
		}
		fscanf(fp1, "%f,", &f);
		route[i].time = f;
		fscanf(fp1, "%f,", &f);
		route[i].cost = f;
		ch = fgetc(fp1);
		for (; ch != '\n'; ch = fgetc(fp1)) {
			route[i].other_information += ch;
		}//读其他信息
		ch = fgetc(fp1);
		i++;
	}
	fclose(fp1);
	cout << "读取数据成功\n" << endl;
}

int Locate(string city, City ct[]) {
	for (int i = 0; i < 199; i++) {
		if (ct[i].city == city)
			return i;
	}
	return 0;
}
//深度优先遍历
void DFS(Graph& g, int i) {
	int j;
	visited[i] = 1;
	cout << g.vertex[i].country << endl;
	for (j = 0;j < g.vexnum;j++) {
		if (g.arcs[i][j].cost != 20000 && !visited[j]) {
			DFS(g, j);
		}
	}
}
//深度优先遍历
void DFStraverse(Graph& g) {
	int i;
	for (i = 0;i < g.vexnum;i++) {
		visited[i] = 0;
	}
	for (i = 0;i < g.vexnum;i++) {
		if (!visited[i]) {
			DFS(g, i);
		}
	}
	cout << "深度优先遍历成功!\n" << endl;
}

void CreatGraph(Graph& g, City* ct, Route* route) {//创建图
	g.arcnum = 199 * 199;
	g.vexnum = 199;
	g.vertex = ct;
	int i = 0, j = 0;
	//初始化边的数据
	for (i = 0; i < 199; i++) {
		for (j = 0; j < 199; j++) {
			if (i == j) {
				g.arcs[i][j].cost = 0;
				g.arcs[i][j].time = 0;
			}
			else {
				g.arcs[i][j].cost = 20000;
				g.arcs[i][j].time = 20000;
			}
		}
	}

	//把边的数据录入邻接矩阵
	for (i = 0; i < 1975; i++) {
		int ord;
		int des;
		ord = Locate(route[i].origin_city, ct);
		des = Locate(route[i].destination_city, ct);
		/*cout << ord << endl;*/
		if (ord && des) {//如果存在ord和des
			
			if (!g.arcs[ord][des].time) {//如果时间不存在
				g.arcs[ord][des].cost = route[i].cost;
				g.arcs[ord][des].time = route[i].time;
				g.arcs[ord][des].transport = route[i].transport;
				g.arcs[ord][des].other_information = route[i].other_information;

			}
			else {//时间存在
				if (g.arcs[ord][des].time >= route[i].time)
				{
					g.arcs[ord][des].time = route[i].time;
					g.arcs[ord][des].transport = route[i].transport;
					g.arcs[ord][des].other_information = route[i].other_information;
				}
				if (g.arcs[ord][des].cost >= route[i].cost)
					g.arcs[ord][des].cost = route[i].cost;

			}//取最小时间和最小金钱,选择最优弧	
		}
	}
	cout << "创建图成功\n " << endl;
}




void shortestPath_DIJ_time(const Graph& g, int depart, int dest, Way way[][199], float dist[][199]) {
	//depart为出发点，dest为终点
	//最短路径指最短时间
	float mintime = 0;
	for (int v = 0; v < g.vexnum; v++) {
		g.vertex[v].pass = false;       //未求得到v的最短路径
		dist[depart][v] = g.arcs[depart][v].time;  //初始化最短路径，初始值为直接路径
		if (dist[depart][v] < 20000) {
			way[v][depart].path = true;
			way[v][v].path = true;      //初始化way数组
			way[v][v].pre = depart;
		}
		else {
			way[v][v].pre = -1;
		}
	}
	dist[depart][depart] = 0;
	g.vertex[depart].pass = true;
	for (int i = 0; i < g.vexnum; i++) {
		int v = 0;                            //v选择一条最短路径
		float min = 20000;                                //当前所知道depart的最近距离，初始为无穷
		for (int w = 0; w < g.vexnum; w++) {  //检查其他所有顶点
			if (g.vertex[w].pass == false) {   //未被并入最短路径
				if (dist[depart][w] < min) {  //比当前最短路径短
					v = w;
					min = dist[depart][w];//取当前路径为最短路径
				}
			}
		}
		g.vertex[v].pass = true;              //最短路径顶点v并入路径
		for (int w = 0; w < g.vexnum; w++) {  //更新当前最短路径及距离
			if (g.vertex[w].pass == false && ((min + g.arcs[v][w].time) < dist[depart][w])) {
				//depart到w的最短路径尚未找到
				//且 depart到v 加 v到w 的最短路径 小于当前 depart到w 最短路径
				dist[depart][w] = min + g.arcs[v][w].time;             //更新depart到w的最短路径长度
				 //depart到w的最短路径的顶点更新为 depart到v 加 v到w 的顶点
				for (int k = 0;k < g.vexnum;k++) {
					way[w][k].path = way[v][k].path;
					way[w][k].pre = way[v][k].pre;//更新w到k点的前驱，达到路径储存的效果
				}
				way[w][w].path = true;
				way[w][w].pre = v;                        //更新路径，储存way路径，便于输出
				mintime = dist[depart][dest];
			}
		}
	}
	cout << mintime << "小时" << endl;//输出时间
}

void shortestPath_DIJ_cost(const Graph& g, int depart, int dest, Way way[][199], float dist[][199]) {
	//最少金钱，与最短时间类似
	float mincost = 0;
	for (int v = 0; v < g.vexnum; v++) {
		g.vertex[v].pass = false;
		dist[depart][v] = g.arcs[depart][v].cost;
		if (dist[depart][v] < 20000) {
			way[v][depart].path = true;
			way[v][v].path = true;
			way[v][v].pre = depart;
		}
		else {
			way[v][v].pre = -1;
		}
	}
	dist[depart][depart] = 0;
	g.vertex[depart].pass = true;

	for (int i = 0; i < g.vexnum; i++) {
		int v = 0;
		float min = 20000;
		for (int w = 0; w < g.vexnum; w++) {
			if (g.vertex[w].pass == false) {
				if (dist[depart][w] < min) {
					v = w;
					min = dist[depart][w];
				}
			}

		}

		g.vertex[v].pass = true;
		for (int w = 0; w < g.vexnum; w++) {
			if (g.vertex[w].pass == false && ((min + g.arcs[v][w].cost) < dist[depart][w])) {

				dist[depart][w] = min + g.arcs[v][w].cost;
				for (int k = 0;k < g.vexnum;k++) {
					way[w][k].path = way[v][k].path;
					way[w][k].pre = way[v][k].pre;
				}
				way[w][w].path = true;
				way[w][w].pre = v;
				mincost = dist[depart][dest];
			}

		}
	}
	cout << mincost << "元" << endl;
}

void print(Graph g, int depart, int dest, Way way[][199], City* ct) {//地图可视化
	stack<int> path;
	int m = dest, k = 0;

	path.push(m);
	while (m != depart) {
		m = way[dest][m].pre;
		path.push(m);
	}
	//while (!path.empty())       //先进后出,获得正序
	//{
	//	cout<<ct[path.top()].country<<endl;//打印堆的头节点
	//	path.pop();            //将堆的头节点弹出
	//}

	FILE* fp3;
	fp3 = fopen("graph.htm", "w");
	if (fp3 == NULL)
	{
		cout << "error3!";
		exit(0);
	}
	//HTML文件头部说明
	std::string s = "<!DOCTYPE html><html><head>\
<style type='text/css'>body, html{width: 100%;height: 100%;margin:0;font-family:'微软雅黑';}#allmap{height:100%;width:100%;}#r-result{width:100%;}</style>\
<script type='text/javascript' src='http://api.map.baidu.com/api?v=2.0&ak=nSxiPohfziUaCuONe4ViUP2N'></script>";

	fprintf(fp3, "%s<title>Shortest path from %s to %s</title></head><body>\
<div id='allmap'></div></div></body></html><script type='text/javascript'>\
var map = new BMap.Map('allmap');\
var point = new BMap.Point(0, 0);\
map.centerAndZoom(point, 2);\
map.enableScrollWheelZoom(true);", s.c_str(), ct[depart].country.c_str(), ct[dest].country.c_str());



	int i = 0; int j = 0;
	//depart是所建图中出发城市对应的顶点号，dest是图中终点城市对应的顶点号
	int bycity = depart, bycity2;

	while (!path.empty()) {
		//路径中一条弧弧头及其信息
		fprintf(fp3, "var marker%d = new BMap.Marker(new BMap.Point(%.4f, %.4f));\
map.addOverlay(marker%d);\n\
var infoWindow%d = new BMap.InfoWindow(\"<p style = 'font-size:14px;'>country: %s<br/>city: %s</p>\");\
marker%d.addEventListener(\"click\", function(){\
this.openInfoWindow(infoWindow%d);}); ", j, ct[bycity].longitude, ct[bycity].latitude, j, j, ct[bycity].country.c_str(), ct[bycity].city.c_str(), j, j);
		cout << ct[path.top()].country << " -> ";
		bycity2 = bycity;
		j++;
		path.pop();
		if (!path.empty()) {
			bycity = path.top();
		}

		//路径中一条弧弧尾及其信息
		fprintf(fp3, "var marker%d = new BMap.Marker(new BMap.Point(%.4f, %.4f));\
map.addOverlay(marker%d);\n\
var infoWindow%d = new BMap.InfoWindow(\"<p style = 'font-size:14px;'>country: %s<br/>city: %s</p>\");\
marker%d.addEventListener(\"click\", function(){\
this.openInfoWindow(infoWindow%d);}); ", j, ct[bycity].longitude, ct[bycity].latitude, j, j, ct[bycity].country.c_str(), ct[bycity].city.c_str(), j, j);

		//路径中一条弧的信息
		fprintf(fp3, "var contentString0%d = '%s, %s --> %s, %s (%s - %.0f hours - $%.0f - %s)';\
var path%d = new BMap.Polyline([new BMap.Point(%.4f, %.4f),new BMap.Point(%.4f, %.4f)], {strokeColor:'#18a45b', strokeWeight:8, strokeOpacity:0.8});\
map.addOverlay(path%d);\
path%d.addEventListener(\"click\", function(){\
alert(contentString0%d);});", j, ct[bycity2].city.c_str(), ct[bycity2].country.c_str(), ct[bycity].city.c_str(), ct[bycity].country.c_str(), g.arcs[bycity2][bycity].transport.c_str(), g.arcs[bycity2][bycity].time, g.arcs[bycity2][bycity].cost, g.arcs[bycity2][bycity].other_information.c_str(), j, ct[bycity2].longitude, ct[bycity2].latitude, ct[bycity].longitude, ct[bycity].latitude, j, j, j);



	}
	fprintf(fp3, "</script>\n");//html文件结束
	fclose(fp3);
}




int main()
{
	City ct[500];
	Route* route = new Route[3000];
	cout << "开始读取数据......" << endl;
	readGraphData(ct, route);
	Graph g;
	cout << "开始创建图......" << endl;
	CreatGraph(g, ct, route);
	Way way[199][199];
	float dist[199][199];
	cout << "开始深度优先遍历,以打印出花费为例：" << endl;
	DFStraverse(g);
	int ord = Locate("Beijing", ct);
	int des = Locate("London", ct);
	cout << "以北京到伦敦最少花费的路线为例，输出路径：" << endl;
	cout << "最少花费为：" << endl;
	shortestPath_DIJ_cost(g, ord, des, way, dist);
	cout << "路径为：" << endl;
	print(g, ord, des, way, ct);
	cout << "路径已保存到graph.html文件中！" << endl;

	return 0;
}

