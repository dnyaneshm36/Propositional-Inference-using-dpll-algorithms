#include<bits/stdc++.h>
using namespace std;

set <string> sentence;
set <char > literal;
char neg = '!';

typedef pair<char, int> pd; 
  
// Structure of the condition 
// for sorting the pair by its 
// second elements 
struct myComp { 
    constexpr bool operator()( 
        pair<char, int> const& a, 
        pair<char, int> const& b) 
        const noexcept 
    { 
        return a.second < b.second; 
    } 
};

void findpuresympbol(set<string> clauses, set <char> symbol ,set<char> &pospure,set<char> &negpure )
{
  for( char ch : symbol){
          for( auto cla : clauses){
            string cl= cla;
             int found = cla.find(ch);
             if(found == string::npos){
               continue;
             }
             else{
                if(cl[found-1]==neg){
                  if(pospure.find(ch)==pospure.end())
                  {
                    negpure.insert(ch);
                  }
                  else 
                  {
                    pospure.erase(ch);
                    break;
                  }
                }
                else 
                {
                  if(negpure.find(ch)==negpure.end())
                  {
                    pospure.insert(ch);
                  }
                  else 
                  {
                    negpure.erase(ch);
                    break;
                  }
                }
             }
          }
      }
}
bool dpll( set<string> clauses, set <char> symbol ,  unordered_multimap <char ,int > model)
{
      int a;
      for(  auto it : model){
          char l = it.first;
          auto  a = clauses.begin();

          while(a!= clauses.end()){
              
               auto temp =a->find(l);
               string str = *a;
             if(a->find(l)!=string::npos)
             {
                if(it.second == 1   )
                {
                  if(str[temp -1] != neg )
                  {
                    a = clauses.erase(a);
                  }
                  else if(str[temp -1] == neg )
                  {
                      if(temp ==0 )
                      {
                        str=str.erase(temp,1);
                        a = clauses.erase(a);
                        clauses.insert(str);
                    }
                      else
                      {
                        str=str.erase(temp-1,2);
                        a = clauses.erase(a);
                        clauses.insert(str);
                      }
                  }
                }
                else if(it.second == 0 )
                {
                  if(str[temp -1] == neg )
                  {
                    a = clauses.erase(a);
                  }else if(str[temp -1] != neg )
                  {
                      if(temp ==0 )
                      {
                        str=str.erase(temp,1);
                        a = clauses.erase(a);
                        clauses.insert(str);
                      }
                      else
                      {
                        str=str.erase(temp-1,2);
                        a = clauses.erase(a);
                        clauses.insert(str);
                      }
                      
                      
                  }
                  
                }
                else {
                  a++;
                }
             }
             else 
             {
               a++;
             }
          }  
      }

      if (clauses.empty())
      {
         cout<<"statiable :\n";
         for(auto temp: model )
         {
           std :: cout<<temp.first<<" "<<temp.second<<endl;
         }
        return true;
      } 
      
      for( auto sym : symbol)
      {
        if(model.count(sym)>1)
        {
          return false;
        }
      }
      // chekcing for the  unit 
      // symbol in clauses;
      bool unitclase = false;
      auto  strit = clauses.begin();
      while ( strit != clauses.end() ){
        string str= *strit;
        int len =str.size();
         if ( len==1 )
         {
           if(model.count(str[0])==0)
          {
            model.insert(make_pair(str[0],1));
          }
            strit = clauses.erase(strit);
            unitclase = true;
         }
         else if(len == 2 )
         {
              if(str[0]= neg)
              {
                if(model.count(str[1])==0)
                {
                  model.insert(make_pair(str[1],0));
                }
                strit = clauses.erase(strit);
                 unitclase = true;
              }
         }
         else
         {
           strit++;
         }

      }
      if ( unitclase )
      {
        return dpll (clauses,symbol,model);
      }
      
      // chekcing for the  pure  
      // symbol in clauses;
      set<char> negpure;
      set<char> pospure;
      findpuresympbol(clauses,symbol,pospure,negpure);

      if(pospure.size() != 0){
          for(char ch  : pospure){
                if(model.count(ch)==0)
                {
                  model.insert(make_pair(ch,1));
                }
                else {
                  return false;
                }
          }
      }
      if(negpure.size() != 0){
          for(char ch  : negpure){
                if(model.count(ch)==0)
                {
                  model.insert(make_pair(ch,0));
                }
                else
                {
                  return false;
                }
                
          }
      }
      if ( negpure.size()!=0 || pospure.size() !=0 )
      {
        return dpll(clauses,symbol,model);
      }

      // find symbol most conttion
      //  in the  clauses
      int count=0;
       priority_queue<pd, vector<pd>, myComp> pq;
      for( char ch : symbol )
      {
        count =0;
          for(string  sec : clauses){
              if(sec.find(ch) != string:: npos)
              {
                count++;
              }
          }
          if(count>0)
          {
            pq.push(make_pair(ch,count));
          }
          
      }
      bool ans=false;
      if( pq.empty())
      {
         return false;
      }
      auto temp = pq.top();
      pq.pop();
      char c  =temp.first;
      if(model.count(c)==0)
      {
         model.insert(make_pair(c,0));
      }
      ans = ans || dpll (clauses,symbol,model);
      model.erase(c);
      if (ans)
      {
        return ans;
      }
      
      if(model.count(c)==0)
      {
         model.insert(make_pair(c,1));
      }

      bool oneans = dpll (clauses,symbol,model);
       ans = ans || oneans;
      

      return ans;


}

int main()
{
    string str;

     ifstream myfile;
      myfile.open ("input.txt");
      while( getline(myfile,str))
      {

          if( str.find("<->") != string:: npos){
            int mid = str.find("<->");
             string a= str.substr(0,mid-2)+" !"+str[mid-1]+" + "+str.substr(mid+3);
                  a.erase(0, 1);
                    a.erase(a.size() - 1);
                   sentence.insert(a);     
          
             a= str.substr(0,mid-2)+" !"+str[mid+3]+" + "+ str[mid-1]+str.substr(mid+4); 
                   a.erase(0, 1);
                    a.erase(a.size() - 1);
                   sentence.insert(a);
          }
          else  if( str.find("->") != string:: npos){
            int mid = str.find("->");
                
                string a= str.substr(0,mid-2)+" !"+str[mid-1]+" + "+str.substr(mid+2);
                a.erase(0, 1);
                    a.erase(a.size() - 1);
                   sentence.insert(a);
          }
          else {
            str.erase(0, 1);
            str.erase(str.size() - 1);
          sentence.insert(str);     
          }
        
      }
       myfile.close();


    for ( auto clause : sentence)
    {
          
          for (char c : clause){
            if(( c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            literal.insert(c);
          }
    }
    set<string > clau = sentence;
    set <char > symbol = literal;
    unordered_multimap <char ,int > model;
    
    /*
    0 for false 
    1 for true
    */
    bool statifiable = dpll( clau , symbol, model);
          if(!statifiable) cout<<" ---- not statifable---- \n"<<endl;
          else cout<< " ----statifable---- \n";
          
 return 0;
}