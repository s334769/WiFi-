#include<bits/stdc++.h>
using namespace std;
string cmd(const string&line)
{
        FILE*f=_popen(line.c_str(),"r");          //popen开一个shell通道 
        string res;
        char b[500];
        while(fgets(b,sizeof b,f))
        {
                res+=b;
        }
        _pclose(f);
        return res;
} 
int main()
{
        string line="netsh wlan show profiles";                        //获取连接过的wifi的ssid 
        string a=cmd(line);
        int cnt=a.size();
        bool g=false;
        int con1=0,con2=0;
        vector<string>pu;
        for(int i=0;i<cnt;i++)
        {
                if(a[i]==':')
                {
                        if(!g)
                        {
                                g=true;
                                cout<<"\n\n\n";
                                continue;
                        }
                        int l=i+=2;
                        while(a[i]!=10)i++;
                        string t=a.substr(l,i-l);
                        string kt=cmd("netsh wlan show profiles name="+("\""+t+"\"")+" key=clear");
                        con1++;
                        //cout<<t<<endl;
                        //cout<<kt<<endl;
                        int cnt=kt.size(),r=0;
                        int d[]={-71,-40,-68,-4,-60,-38,-56,-35};                        //“关键内容”转成int 
                        bool h=false;
                        for(int j=0;j<cnt;j++)
                        {
                                if(kt[j]==d[r])                        //比对找到密码所在 
                                {
                                        r++;
                                        if(r==7)
                                        {
                                                while(kt[j]!=':')j++;
                                                int l=j+=2;
                                                while(kt[j]!=10)j++;
                                                cout<<"\t\t"<<t<<"："<<kt.substr(l,j-l)<<endl;
                                                con2++;
                                                h=true;
                                                break;
                                        }
                                }
                                else r=0;
                        }
                        if(!h)pu.push_back(t);        
                }         
        }
        printf("\n\t   共查询到%d条记录，已打印%d条。\n",con1,con2);
        printf("\n\t    以下wifi无密码：\n");
        for(auto i:pu)cout<<"\n\t\t\t"<<i<<endl;
        //cout<<a;
}
