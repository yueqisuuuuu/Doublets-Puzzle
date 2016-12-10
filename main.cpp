#include <iostream>
#include <fstream>
#include "graph.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

bool edge(string a, string b){
    int count = 5;
    for(size_t i=0; i<5; ++i){
        if(a[i]==b[i]){
            count--;
        }
    }
    return (count==1);
}

int main()
{
    graph g;
    string temp;
    vector<string> d;
    ifstream is("/Users/yueqisu/Dropbox/SCU/2016-17/FALL 16/CSCI 61/HW/HW8/knuth.txt");
    if (is.fail()){
        cout<<"Can't open dictionary!"<<endl;
        exit(1);
    }

    while (is>>temp){
        d.push_back(temp);
    }
    is.close();

    for (size_t i=0; i<d.size(); ++i){
          g.add_vertex();
      }

    for (size_t i=0; i<d.size(); ++i){
        for(size_t j=i+1; j<d.size();++j){
            if (edge(d[i], d[j])==true){
                g.add_edge(i,j);
            }
        }
    }

    ifstream in("/Users/yueqisu/Dropbox/SCU/2016-17/FALL 16/CSCI 61/HW/HW8/puzzle.txt");
    if (in.fail()){
        cout<<"Can't open puzzle!"<<endl;
        exit(1);
    }
    string start, end;
    vector< pair <string, string> > puzzle;
    while (in>>start){
        in>>end;
        pair<string, string> p (start, end);
        puzzle.push_back(p);
    }

     in.close();


    for(auto e: puzzle){
        start=e.first;
        end=e.second;
    cout<<"Start Phrase: "<<start<<", End Phrase: "<<end<<endl;
    std::size_t source, dest;
    for (source=0; d[source]!=start; source++){}
    for (dest=0; d[dest]!=end; dest++){}

    vector<size_t> solution = g.shortest_path(source, dest);

    if (solution.size()==0){
        cout<<"No solution found"<<endl;
    }

    else {
        for (int i=solution.size()-1; i>=0; i--){
            int j=solution[i];
            cout<<d[j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


    return 0;
}
