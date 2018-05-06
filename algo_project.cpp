#include<iostream>
#include<cstdio>
#include<ctime>
#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>
#include<conio.h>
#include<cstdlib>
using namespace std;
struct Edge
{
    int src;
    int dest;
    int weight;
};
struct subset
{
    int rank;
    int parent;
};
struct Graph
{
    int v;
    int e;
    struct Edge *edges;
};
int vertice,z;
int *a;
int *b;    //they will store x and y coordinates of vertex

Graph *create_graph(int a,int x)
{
    Graph *graph=new Graph;
    graph->v=a;
    graph->e=x;
    graph->edges=new struct Edge[x];
    return graph;
}
void draw_graph()
{
    int x,y,width=17;
    char str[3];
    srand(time(NULL));
    for(int j=0;j<vertice;j++)
    {
        bool notfulfill;
        do{
            notfulfill = false;
            x=(rand()%(609-30+1))+30;
            y=(rand()%(450-30+1))+30;

            for(int i = 0; i<j; i++){
                if(x < a[i]+10 && x > a[i]-10){
                    notfulfill = true;
                    break;
                }
                if(y < b[i]+10 && y > b[i]-10){
                    notfulfill = true;
                    break;
                }
            }
        }while(notfulfill);
        a[j]=x;
        b[j]=y;
        circle(a[j],b[j],width);
        setfillstyle(SOLID_FILL,LIGHTBLUE);
        floodfill(a[j],b[j],WHITE);
        sprintf(str,"%d",j);
        setbkcolor(LIGHTBLUE);
        setcolor(BLACK);
        outtextxy(a[j],b[j],str);
        setcolor(WHITE);
        setbkcolor(BLACK);
    }
    //filling the background
    /*setfillstyle(HATCH_FILL,RED);
    floodfill(0,0,WHITE);*/
}
void drawline(Graph *graph)
{
    char str[3];
    int x,y,z;
   for(int i=0;i<graph->e;i++)
   {
       x=graph->edges[i].src;
       y=graph->edges[i].dest;
       z=graph->edges[i].weight;
        line(a[x],b[x],a[y],b[y]);
        sprintf(str,"%d",z);
        outtextxy((a[x]+a[y])/2,(b[x]+b[y])/2,str);
   }
}

void gotoxy(int x,int y)
{
    COORD coord={0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int mycomp(const void *a,const void *b)
{
    struct Edge *a1=(struct Edge*)a;
    struct Edge *a2=(struct Edge*)b;
    return a1->weight>a2->weight;
}
int find_set(struct subset subsets[],int i)
{
    if(subsets[i].parent!=i)
        subsets[i].parent=find_set(subsets,subsets[i].parent);
    return subsets[i].parent;
}
void union_set(struct subset subsets[],int x,int y)
{
    int xroot=find_set(subsets,x);
    int yroot=find_set(subsets,y);
    if(subsets[xroot].rank<subsets[yroot].rank)
        subsets[xroot].parent=yroot;
    else if(subsets[xroot].rank>subsets[yroot].rank)
        subsets[yroot].parent=xroot;
    else
    {
        subsets[yroot].parent=xroot;
        subsets[xroot].rank++;
    }
}
void draw_MST(struct Edge result[],int k)
{
    int x,y,z;
    int cost=0;
    int row=0,col=400;
    char str[3];
    char str2[25]; //to print edges
    delay(3000);
    outtextxy(150,10,"Now This is the Kruskal Minimum Spanning Tree");
    outtextxy(0,385,"Edges in MST");
    for(int i=0;i<k;i++)
    {
        x=result[i].src;
        y=result[i].dest;
        z=result[i].weight;
        cost=cost+z;
        setcolor(LIGHTGREEN);
        circle(a[x],b[x],17);
        setcolor(YELLOW);
        setbkcolor(LIGHTBLUE);
        line(a[x],b[x],a[y],b[y]);
        sprintf(str,"%d",x);
        outtextxy(a[x],b[x],str);
        sprintf(str,"%d",y);
        outtextxy(a[y],b[y],str);
        delay(1000);
       /* circle(a[x],b[x],17);
        setfillstyle(SOLID_FILL,RED);
        floodfill(a[x],b[x],RED);*/
        setcolor(WHITE);
        setbkcolor(BLACK);
        sprintf(str2,"%d======%d------>%d",x,y,z);
        if(col>475)
        {
            col=400;
            row=row+140;
        }
         outtextxy(row,col,str2);
         col=col+15;
         setcolor(RED);
    }
    setcolor(WHITE);
    sprintf(str2,"Total Cost of Laying wire=%d",cost);
    outtextxy(row,col,str2);
}
void kruskalMST(Graph *graph)
{
    int s=graph->v;
    int i=0;
    int y=0;
    struct Edge result[s];

    qsort(graph->edges,graph->e,sizeof(graph->edges[0]),mycomp);

    struct subset *subsets=new subset[s];
    for(int k=0;k<s;k++)
    {
        subsets[k].rank=0;
        subsets[k].parent=k;
    }
    while(y<s-1)
    {
        struct Edge next_edge=graph->edges[i++];
        int x=find_set(subsets,next_edge.src);
        int z=find_set(subsets,next_edge.dest);
        if(x!=z)
        {
            result[y++]=next_edge;
            union_set(subsets,x,z);
        }
        //else discard the edge

    }
    /*
    for(int k=0;k<y;k++)
    {
        cout<<result[k].src<<"====="<<result[k].dest<<"---->"<<result[k].weight<<"\n";
    }
    */
  setcolor(WHITE);
   draw_MST(result,y);

    return;
}
int main()
{
    int gd=0,gm;
    char driver[]="";


    gotoxy(46,12);
    cout<<"ENTER NO. OF VERTICES=";
    cin>>vertice;
    a=new int[vertice];
    b=new int[vertice];
    system("cls");
    gotoxy(46,12);
    cout<<"ENTER NO. OF EDGES=";
    cin>>z;
    //vertice is no. of vertices of graph and z is the no. of edges
     Graph *graph=create_graph(vertice,z);
     system("cls");
     for(int i=0;i<z;i++)
     {
         gotoxy(46,12);
         cout<<"ENTER VALUES FOR EDGE "<<i+1;
         gotoxy(46,16);
         cout<<"Enter source=";
         cin>>graph->edges[i].src;
         gotoxy(46,20);
         cout<<"Enter Destination=";
         cin>>graph->edges[i].dest;
         gotoxy(46,24);
         cout<<"Enter Weight=";
         cin>>graph->edges[i].weight;
         system("cls");
     }

    initgraph(&gd,&gm,driver);
  /*  Graph *graph=create_graph(vertice,z);
   //edge 0
   graph->edges[0].src=0;
   graph->edges[0].dest=1;
   graph->edges[0].weight=10;

   //edge 1
   graph->edges[1].src=0;
   graph->edges[1].dest=2;
   graph->edges[1].weight=6;

   //edge 2
   graph->edges[2].src=0;
   graph->edges[2].dest=3;
   graph->edges[2].weight=5;


   //edge 3
   graph->edges[3].src=1;
   graph->edges[3].dest=3;
   graph->edges[3].weight=15;

   //edge 4
   graph->edges[4].src=2;
   graph->edges[4].dest=3;
   graph->edges[4].weight=4;
*/
    draw_graph();
   drawline(graph);
   outtextxy(250,10,"This is the Graph");
   kruskalMST(graph);
   getch();
   closegraph();
   return 0;
}
