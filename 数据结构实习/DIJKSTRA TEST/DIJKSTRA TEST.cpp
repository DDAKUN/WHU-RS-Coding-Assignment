
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;
bool visited[20000];//���ʽ��ı�־

typedef struct route
{
	string origin_city, destination_city, transport, other_information;
	float time, cost;
}Route, Arcs;


typedef struct city
{   //����
	bool pass = false;
	string country, city;
	float latitude, longitude;
}City, Vertex;


struct Graph {  //�ڽӾ���
	Vertex* vertex;
	Arcs arcs[199][199];
	int vexnum, arcnum;
};

struct Way {
	int path;
	int pre;
};

void readGraphData(City* ct, Route* route) {
	/*cout << "���ļ���ʼ" << endl;*/
	int i = 0, j = 0;  //ѭ������
	//��ȡ����(����)�����ļ�
	FILE* fp = fopen("cities.csv", "r");
	if (!fp) {
		cout << "error1!";
		exit(0);
	}
	char ch;
	float f;
	while (!feof(fp)) {
		//���ζ�ȡ������������������һ��
		ch = fgetc(fp);
		for (; ch != ','; ch = fgetc(fp)) {
			ct[i].country += ch;
		}
		/*cout << ct[i].country << ",";*/
		ch = fgetc(fp);    //��������
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

	//��ȡ·���ļ�
	FILE* fp1 = fopen("routes.csv", "r");
	if (!fp1) {
		cout << "error2!";
		exit(0);
	}

	i = 0;
	ch = fgetc(fp1);
	while (!feof(fp1)) {
		//���ζ�ȡ������������������һ��
		for (; ch != ','; ch = fgetc(fp1)) {
			route[i].origin_city += ch;
		}
		ch = fgetc(fp1);//��������
		for (; ch != ','; ch = fgetc(fp1)) {
			route[i].destination_city += ch;
		}
		ch = fgetc(fp1);//��������
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
		}//��������Ϣ
		ch = fgetc(fp1);
		i++;
	}
	fclose(fp1);
	cout << "��ȡ���ݳɹ�\n" << endl;
}

int Locate(string city, City ct[]) {
	for (int i = 0; i < 199; i++) {
		if (ct[i].city == city)
			return i;
	}
	return 0;
}
//������ȱ���
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
//������ȱ���
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
	cout << "������ȱ����ɹ�!\n" << endl;
}

void CreatGraph(Graph& g, City* ct, Route* route) {//����ͼ
	g.arcnum = 199 * 199;
	g.vexnum = 199;
	g.vertex = ct;
	int i = 0, j = 0;
	//��ʼ���ߵ�����
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

	//�ѱߵ�����¼���ڽӾ���
	for (i = 0; i < 1975; i++) {
		int ord;
		int des;
		ord = Locate(route[i].origin_city, ct);
		des = Locate(route[i].destination_city, ct);
		/*cout << ord << endl;*/
		if (ord && des) {//�������ord��des
			
			if (!g.arcs[ord][des].time) {//���ʱ�䲻����
				g.arcs[ord][des].cost = route[i].cost;
				g.arcs[ord][des].time = route[i].time;
				g.arcs[ord][des].transport = route[i].transport;
				g.arcs[ord][des].other_information = route[i].other_information;

			}
			else {//ʱ�����
				if (g.arcs[ord][des].time >= route[i].time)
				{
					g.arcs[ord][des].time = route[i].time;
					g.arcs[ord][des].transport = route[i].transport;
					g.arcs[ord][des].other_information = route[i].other_information;
				}
				if (g.arcs[ord][des].cost >= route[i].cost)
					g.arcs[ord][des].cost = route[i].cost;

			}//ȡ��Сʱ�����С��Ǯ,ѡ�����Ż�	
		}
	}
	cout << "����ͼ�ɹ�\n " << endl;
}




void shortestPath_DIJ_time(const Graph& g, int depart, int dest, Way way[][199], float dist[][199]) {
	//departΪ�����㣬destΪ�յ�
	//���·��ָ���ʱ��
	float mintime = 0;
	for (int v = 0; v < g.vexnum; v++) {
		g.vertex[v].pass = false;       //δ��õ�v�����·��
		dist[depart][v] = g.arcs[depart][v].time;  //��ʼ�����·������ʼֵΪֱ��·��
		if (dist[depart][v] < 20000) {
			way[v][depart].path = true;
			way[v][v].path = true;      //��ʼ��way����
			way[v][v].pre = depart;
		}
		else {
			way[v][v].pre = -1;
		}
	}
	dist[depart][depart] = 0;
	g.vertex[depart].pass = true;
	for (int i = 0; i < g.vexnum; i++) {
		int v = 0;                            //vѡ��һ�����·��
		float min = 20000;                                //��ǰ��֪��depart��������룬��ʼΪ����
		for (int w = 0; w < g.vexnum; w++) {  //����������ж���
			if (g.vertex[w].pass == false) {   //δ���������·��
				if (dist[depart][w] < min) {  //�ȵ�ǰ���·����
					v = w;
					min = dist[depart][w];//ȡ��ǰ·��Ϊ���·��
				}
			}
		}
		g.vertex[v].pass = true;              //���·������v����·��
		for (int w = 0; w < g.vexnum; w++) {  //���µ�ǰ���·��������
			if (g.vertex[w].pass == false && ((min + g.arcs[v][w].time) < dist[depart][w])) {
				//depart��w�����·����δ�ҵ�
				//�� depart��v �� v��w �����·�� С�ڵ�ǰ depart��w ���·��
				dist[depart][w] = min + g.arcs[v][w].time;             //����depart��w�����·������
				 //depart��w�����·���Ķ������Ϊ depart��v �� v��w �Ķ���
				for (int k = 0;k < g.vexnum;k++) {
					way[w][k].path = way[v][k].path;
					way[w][k].pre = way[v][k].pre;//����w��k���ǰ�����ﵽ·�������Ч��
				}
				way[w][w].path = true;
				way[w][w].pre = v;                        //����·��������way·�����������
				mintime = dist[depart][dest];
			}
		}
	}
	cout << mintime << "Сʱ" << endl;//���ʱ��
}

void shortestPath_DIJ_cost(const Graph& g, int depart, int dest, Way way[][199], float dist[][199]) {
	//���ٽ�Ǯ�������ʱ������
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
	cout << mincost << "Ԫ" << endl;
}

void print(Graph g, int depart, int dest, Way way[][199], City* ct) {//��ͼ���ӻ�
	stack<int> path;
	int m = dest, k = 0;

	path.push(m);
	while (m != depart) {
		m = way[dest][m].pre;
		path.push(m);
	}
	//while (!path.empty())       //�Ƚ����,�������
	//{
	//	cout<<ct[path.top()].country<<endl;//��ӡ�ѵ�ͷ�ڵ�
	//	path.pop();            //���ѵ�ͷ�ڵ㵯��
	//}

	FILE* fp3;
	fp3 = fopen("graph.htm", "w");
	if (fp3 == NULL)
	{
		cout << "error3!";
		exit(0);
	}
	//HTML�ļ�ͷ��˵��
	std::string s = "<!DOCTYPE html><html><head>\
<style type='text/css'>body, html{width: 100%;height: 100%;margin:0;font-family:'΢���ź�';}#allmap{height:100%;width:100%;}#r-result{width:100%;}</style>\
<script type='text/javascript' src='http://api.map.baidu.com/api?v=2.0&ak=nSxiPohfziUaCuONe4ViUP2N'></script>";

	fprintf(fp3, "%s<title>Shortest path from %s to %s</title></head><body>\
<div id='allmap'></div></div></body></html><script type='text/javascript'>\
var map = new BMap.Map('allmap');\
var point = new BMap.Point(0, 0);\
map.centerAndZoom(point, 2);\
map.enableScrollWheelZoom(true);", s.c_str(), ct[depart].country.c_str(), ct[dest].country.c_str());



	int i = 0; int j = 0;
	//depart������ͼ�г������ж�Ӧ�Ķ���ţ�dest��ͼ���յ���ж�Ӧ�Ķ����
	int bycity = depart, bycity2;

	while (!path.empty()) {
		//·����һ������ͷ������Ϣ
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

		//·����һ������β������Ϣ
		fprintf(fp3, "var marker%d = new BMap.Marker(new BMap.Point(%.4f, %.4f));\
map.addOverlay(marker%d);\n\
var infoWindow%d = new BMap.InfoWindow(\"<p style = 'font-size:14px;'>country: %s<br/>city: %s</p>\");\
marker%d.addEventListener(\"click\", function(){\
this.openInfoWindow(infoWindow%d);}); ", j, ct[bycity].longitude, ct[bycity].latitude, j, j, ct[bycity].country.c_str(), ct[bycity].city.c_str(), j, j);

		//·����һ��������Ϣ
		fprintf(fp3, "var contentString0%d = '%s, %s --> %s, %s (%s - %.0f hours - $%.0f - %s)';\
var path%d = new BMap.Polyline([new BMap.Point(%.4f, %.4f),new BMap.Point(%.4f, %.4f)], {strokeColor:'#18a45b', strokeWeight:8, strokeOpacity:0.8});\
map.addOverlay(path%d);\
path%d.addEventListener(\"click\", function(){\
alert(contentString0%d);});", j, ct[bycity2].city.c_str(), ct[bycity2].country.c_str(), ct[bycity].city.c_str(), ct[bycity].country.c_str(), g.arcs[bycity2][bycity].transport.c_str(), g.arcs[bycity2][bycity].time, g.arcs[bycity2][bycity].cost, g.arcs[bycity2][bycity].other_information.c_str(), j, ct[bycity2].longitude, ct[bycity2].latitude, ct[bycity].longitude, ct[bycity].latitude, j, j, j);



	}
	fprintf(fp3, "</script>\n");//html�ļ�����
	fclose(fp3);
}




int main()
{
	City ct[500];
	Route* route = new Route[3000];
	cout << "��ʼ��ȡ����......" << endl;
	readGraphData(ct, route);
	Graph g;
	cout << "��ʼ����ͼ......" << endl;
	CreatGraph(g, ct, route);
	Way way[199][199];
	float dist[199][199];
	cout << "��ʼ������ȱ���,�Դ�ӡ������Ϊ����" << endl;
	DFStraverse(g);
	int ord = Locate("Beijing", ct);
	int des = Locate("London", ct);
	cout << "�Ա������׶����ٻ��ѵ�·��Ϊ�������·����" << endl;
	cout << "���ٻ���Ϊ��" << endl;
	shortestPath_DIJ_cost(g, ord, des, way, dist);
	cout << "·��Ϊ��" << endl;
	print(g, ord, des, way, ct);
	cout << "·���ѱ��浽graph.html�ļ��У�" << endl;

	return 0;
}

