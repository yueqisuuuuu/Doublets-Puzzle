#include <iostream>
#include <fstream>
#include "graph.h"
#include <string>
#include <vector>
#include <map>
#include <cassert>

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

vector< pair <string, string> > open_puzzle(string file){
     ifstream in(file);
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
      return puzzle;
 }

void find_solution(string start, string end, graph &g, const vector<string> &d){
    assert(start.length()==5 && end.length()==5);
    cout<<"Start Phrase: "<<start<<", End Phrase: "<<end<<endl;
    std::size_t source, dest;
    for (source=0; d[source]!=start && source<d.size(); source++){}
    for (dest=0; d[dest]!=end && dest<d.size(); dest++){}
    if (source==d.size() || dest ==d.size()){
        cout<<"Not a Valid Word"<<endl<<endl;
        return;
    }
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
    string ip, start, end;
    cout<<"This is a word-morph for 5-letter words."<<endl;
    cout<<"Input or File Upload?"<<endl;
    getline(cin,ip);

    while (ip!="end" || ip!="End"){
        if (ip=="input"||ip=="Input"){
            cout<<"ip: "<<ip<<endl;
            cout<<"Start Phrase: ";
            cin>>start;
            cout<<"End Phrase: ";
            cin>>end;
            find_solution(start, end, g, d);
            getline(cin,ip); //dummy getline
        }
        else if (ip=="file upload"||ip=="File upload"||ip=="File Upload"){
            string file;
            cout<<"File Location: ";
            getline(cin, file);
            vector< pair <string, string> > puzzle=open_puzzle(file);

            for(auto e: puzzle){
                start=e.first;
                end=e.second;
            find_solution(start, end, g, d);
        }
        }
        else if(ip=="end" || ip=="End"){
            break;
        }
        else{
            cout<<"Invalid Input! Try Again!"<<endl;
        }

        cout<<"Another input or file upload? Or enter \"end\" to exit."<<endl;
        getline(cin,ip);
    }

    return 0;
}
