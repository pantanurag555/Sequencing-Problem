#include<iostream>
#include<stdio.h>
#include<limits.h>

using namespace std;

int main()
{
    int n,m,i,j,k,left,right,min_1=INT_MAX,min_n=INT_MAX,max_mid=-1,tmp,min_val,min_pos_i,min_pos_j,total_time,total_idle_time=0;
    cout<<"Enter the number of jobs ";
    cin>>n;
    cout<<"Enter the number of machines ";
    cin>>m;
    int time[m][n],ini_sch[3][n],fin_sch[n],mch_total_time[m],sch_total_time[n],mach[m][n][2];
    for(i=0;i<m;i++)
    {
        mch_total_time[i]=0;
        cout<<"Enter the time taken(in a sequential order) for jobs in machine "<<i+1<<endl;
        for(j=0;j<n;j++)
        {
            cin>>time[i][j];
            mch_total_time[i]+=time[i][j];
        }
    }
    for(i=0;i<n;i++)
    {
        sch_total_time[i]=0;
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<n;j++)
        {
            ini_sch[i][j]=0;
        }
    }
    if(m>=2)
    {
        for(i=0;i<n;i++)
        {
            if(time[0][i]<=min_1)
            {
                min_1=time[0][i];
            }
            if(time[m-1][i]<=min_n)
            {
                min_n=time[m-1][i];
            }
        }
        for(i=1;i<m-1;i++)
        {
            for(j=0;j<n;j++)
            {
                if(time[i][j]>=max_mid)
                {
                    max_mid=time[i][j];
                }
            }
        }
        if(min_1>=max_mid || min_n>=max_mid)
        {
            for(i=0;i<m;i++)
            {
                for(j=0;j<n;j++)
                {
                    if(i==0)
                    {
                        ini_sch[0][j]=j;
                        ini_sch[1][j]+=time[i][j];
                    }
                    else if(i==m-1)
                    {
                        ini_sch[2][j]+=time[i][j];
                    }
                    else
                    {
                        ini_sch[1][j]+=time[i][j];
                        ini_sch[2][j]+=time[i][j];
                    }
                }
            }
        }
        else
        {
            cout<<"Job scheduling is not possible because the conditions specified by Johnson's Law are not met.";
            goto last;
        }
    }
    else
    {
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                if(i==0)
                {
                    ini_sch[0][j]=j;
                }
                ini_sch[i+1][j]=time[i][j];
            }
        }
    }
    tmp=n;
    left=0;
    right=n-1;
    for(i=0;i<n;i++)
    {
        for(j=1;j<3;j++)
        {
            sch_total_time[i]+=ini_sch[j][i];
        }
    }
    while(tmp)
    {
        min_val=INT_MAX;
        for(i=1;i<3;i++)
        {
            for(j=0;j<tmp;j++)
            {
                if(ini_sch[i][j]<min_val)
                {
                    min_val=ini_sch[i][j];
                    min_pos_i=i;
                    min_pos_j=j;
                }
                else if(ini_sch[i][j]==min_val)
                {
                    if(min_pos_i==i)
                    {
                        if(sch_total_time[ini_sch[0][j]]<sch_total_time[ini_sch[0][min_pos_j]])
                        {
                            min_pos_i=i;
                            min_pos_j=j;
                        }
                    }
                }
            }
        }
        if(min_pos_i==1)
        {
            fin_sch[left]=ini_sch[0][min_pos_j];
            left++;
        }
        else
        {
            fin_sch[right]=ini_sch[0][min_pos_j];
            right--;
        }
        tmp--;
        for(i=0;i<3;i++)
        {
            for(j=min_pos_j;j<tmp;j++)
            {
                ini_sch[i][j]=ini_sch[i][j+1];
            }
        }

    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            for(k=0;k<2;k++)
            {
                if(i==0)
                {
                    if(j==0)
                    {
                        if(k==0)
                        {
                            mach[j][i][k]=0;
                        }
                        else
                        {
                            mach[j][i][k]=time[j][fin_sch[i]];
                        }
                    }
                    else
                    {
                        if(k==0)
                        {
                            mach[j][i][k]=mach[j-1][i][1];
                        }
                        else
                        {
                            mach[j][i][k]=mach[j][i][0]+time[j][fin_sch[i]];
                        }
                    }
                }
                else
                {
                    if(j==0)
                    {
                        if(k==0)
                        {
                            mach[j][i][k]=mach[j][i-1][1];
                        }
                        else
                        {
                            mach[j][i][k]=mach[j][i][0]+time[j][fin_sch[i]];
                        }
                    }
                    else
                    {
                        if(k==0)
                        {
                            if(mach[j-1][i][1]>mach[j][i-1][1])
                            {
                                mach[j][i][k]=mach[j-1][i][1];
                            }
                            else
                            {
                                mach[j][i][k]=mach[j][i-1][1];
                            }
                        }
                        else
                        {
                            mach[j][i][k]=mach[j][i][0]+time[j][fin_sch[i]];
                        }
                    }
                }
                if(i==n-1 && j==m-1 && k==1)
                {
                    total_time=mach[j][i][k];
                }
            }
        }
    }
    /*for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            for(k=0;k<2;k++)
            {
                cout<<mach[j][i][k]<<" ";
            }
            cout<<"   ";
        }
        cout<<endl;
    }*/
    cout<<endl;
    cout<<"The optimum order of job sequencing is: "<<endl<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"Job "<<fin_sch[i]+1;
        if(i!=n-1)
        {
            cout<<"->";
        }
    }
    cout<<endl<<endl;
    cout<<"The total elapsed time is "<<total_time<<endl<<endl;
    for(i=0;i<m;i++)
    {
        cout<<"The idle time for Machine "<<i+1<<" is "<<total_time-mch_total_time[i]<<endl;
        total_idle_time+=total_time-mch_total_time[i];
    }
    cout<<endl;
    cout<<"The total idle time of system is "<<total_idle_time;
    last:;
}
