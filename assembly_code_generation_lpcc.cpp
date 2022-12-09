#include<set>
#include<string>
#include<vector>
#include<iostream>
#include<map>
using namespace std;

//declaring the global storage for storing the terminal as well as non-terminal symbols
set<string>terminal_symbols,non_terminal_symbols;
// for making the columns of quadruple table we use vector of string optr(operator),arg1(operand1),arg2(operand2),result and global input array of terms
vector<string> optr,operand1,operand2,result,strInput;

// utility function for checking whether the given character is a operator or not 
bool isOperator(char &c){
    return c=='*' or c=='+' or c=='-' or c=='/';
}
// utility function to return a string of type of operator
string oper(string a)
{
    if(a=="+")
    {
        return "ADD";
    }
    else if(a=="-")
    {
        return "SUB";
    }
    else if(a=="*")
    {
        return "MULT";
    }
    else
    {
        return "DIV";
    }
}
// a utility function to get the terminal from the term in the three address code 
void getTerminalAndNonTerminal(string &t1){
    string tmp="";
// we traverse through the given in out string to find the terminals and non terminal symbols 
    for(int i=0;i<t1.length();i++){
        while(t1[i]!='=' and non_terminal_symbols.find(tmp)==non_terminal_symbols.end()){
            tmp+=t1[i];
            i++;
        }
        non_terminal_symbols.insert(tmp);
    }
    // find the terminal symbol here after from the = sign till the operator
     for(int i=0;i<t1.length();i++){
        string tmp1="";
        while(t1[i]!='='){
            i++;
        }
        i++;
        while(!isOperator(t1[i])){
            tmp1+=t1[i];
            i++;
        }
        i++;
        if(non_terminal_symbols.find(tmp1)==non_terminal_symbols.end()){
            terminal_symbols.insert(tmp1);
        }
        tmp1="";
        while(i!=t1.length()-1){
            tmp1+=t1[i];
            i++;
        }
        tmp1+=t1[i];
         if(non_terminal_symbols.find(tmp1)==non_terminal_symbols.end()){
            terminal_symbols.insert(tmp1);
        }
    }
}

// we use this function to generate the quadruple table and store in them global storage containers declared above 
void generate_table(string &t1){
    int i=0, j=0,k=0;
    for(i;i<t1.length();i++)
    {
        if(t1[i]=='=')
        {
            j=i;
        }
        if(isOperator(t1[i]))
        {
            k=i;
            break;
        }
    }

    string arg1=t1.substr(j+1,k-j-1);
    string arg2=t1.substr(k+1,t1.length()-1);
    string res="";
    int t=0;
    while(t<j){
        res+=t1[t];
        t++;
    }
    operand1.push_back(arg1);
    operand2.push_back(arg2);
    string opert="";
    opert+=t1[k];
    optr.push_back(opert);
    result.push_back(res);
}
// an utility function to display the quadruple table 
void display()
{
    cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB"<<endl;
    cout<<"\xBA  Operator \t\xBA arg1 \t\xBA arg2 \t\xBAresult\xBA"<<endl;
    cout<<"\xBA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBA"<<endl;
    for(int i=0;i<result.size();i++)
    {
        cout<<"\xBA     "<<optr[i]<<"\t\t\xBA   "<<operand1[i]<<"\t\xBA   "<<operand2[i]<<"\t\xBA  "<<result[i]<<"  \xBA"<<endl;
    }
    cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC"<<endl;
}
// the most important function to display the assembly code of the given three address code 
void create_assembly_code(string &t1,int &cnt){
       string op1=operand1[cnt],op2=operand2[cnt];
       if(op1=="")                                           // HANDLING UNARY OPERATOR
       {
            cout<<"MOV "<<op2<<", R"<<cnt<<endl;
            cout<<"SUB 0, R"<<cnt<<endl;
            cnt++;
       }
     else if(terminal_symbols.find(op1)!=terminal_symbols.end() and terminal_symbols.find(op2)!=terminal_symbols.end()){
          cout<<"MOV"<<" "<<op1<<", R"<<cnt<<endl;
          cout<<oper(optr[cnt])<<" "<<op2<<", R"<<cnt<<endl;
          cnt++;
       }
       else if(non_terminal_symbols.find(op1)!=non_terminal_symbols.end() and terminal_symbols.find(op2)!=terminal_symbols.end()){
          cout<<"MOV"<<" "<<op2<<"R"<<cnt<<endl;
          auto it=non_terminal_symbols.find(op1);
          int p=distance(non_terminal_symbols.begin(),it);
          cout<<oper(optr[cnt])<<" R "<<p<<", R"<<cnt<<endl;
          cnt++;
       }
       else if(terminal_symbols.find(op1)!=terminal_symbols.end() and non_terminal_symbols.find(op2)!=non_terminal_symbols.end()){
          cout<<"MOV"<<" "<<op1<<"R"<<cnt<<endl;
          auto it1=non_terminal_symbols.find(op2);
          int p=distance(non_terminal_symbols.begin(),it1);
          cout<<oper(optr[cnt])<<" R "<<p<<", R"<<cnt<<endl;
          cnt++;
       }
       else
       {
         auto it2=non_terminal_symbols.find(op1);
         int p=distance(non_terminal_symbols.begin(),it2);
         auto it3=non_terminal_symbols.find(op2);
          int q=distance(non_terminal_symbols.begin(),it3);
        cout<<oper(optr[cnt])<<" R"<<p<<", R"<<q<<endl;
         cout<<"MOV R"<<p<<", R"<<cnt<<endl;
        cnt++;
       }

}
int main()
{
    // WE TAKE INPUT OF EACH THREE ADDRESS LINE USING THE STRING AND PUSHBACK IT IN A VECTOR
    string t1="t=a-b";
    string t2="u=a-c";
    string t3="v=t+u";
    string t4="d=v+u";
    strInput.push_back(t1);
    strInput.push_back(t2);
    strInput.push_back(t3);
    strInput.push_back(t4);
    for(int i=0;i<strInput.size();i++){
        getTerminalAndNonTerminal(strInput[i]);
        generate_table(strInput[i]);
    }
    // DISPLAY THE QUADRUPLE TABLE 
    display();
    // cnt variable is to get the count of registers to be used 
    int cnt=0;
    cout<<"============================================================"<<endl<<"ASSEMBLY CODE"<<endl;
    for(int i=0;i<strInput.size();i++){
       create_assembly_code(strInput[i],cnt);
    }
    cout<<"============================================================"<<endl;
    return 0;
}