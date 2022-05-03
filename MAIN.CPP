#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<ctime>
#define TEXT 100001
#define PIC 1001
#define DICT 11
#define SAV 26
#define TAG 10001
#define ED 21
using namespace std;
void eds();
string svoid;
bool finished,_ulock[31],ulock[31],ued[31];
int curf,lasf,sav[SAV],tag[TAG],_chapbeg[31],chapbeg[31],ilock,_ilock,ied,edbeg[ED];
string dat="0123456789ABCDFGHIJKMOPQRTUVWXYZ";
struct s_text
{
	bool is_op;
	bool is_bann;
	bool is_eoc;
	bool is_eos;
	int len;
	int pic;
	string str[4];
	int targ[4];
	int nxt;
	int ulk;
	int chap;
	int ed;
	//chap<0:EX chap>=0:Normal
	string cset;
	s_text(){is_op=0;len=0;ed=-1;pic=14;nxt=0;cset="07";ulk=0;}
}text[TEXT];
struct s_pic
{
	int len;
	string str[31];
	s_pic(){len=0;}
}pic[PIC],dict[DICT];
void printpic(int num)
{
	for(int i=0;i<pic[num].len;i++)cout<<pic[num].str[i]<<endl;
}
void printdic(int num)
{
	for(int i=0;i<dict[num].len;i++)cout<<dict[num].str[i]<<endl;
}
void ccolor(string arg)
{
	system(("color "+arg).c_str());
}
void ccls()
{
	system("cls");
}
bool sure()
{
	ccolor("47");
	printpic(18);
	int cho=system("choice /c YN");
	ccolor("07");
	return (bool)(2-cho);
}
void cpause(bool arg)
{
	//0:pure 1:default
	if(arg)system("pause");
	else system("pause>nul");
}
void calc()
{
	int ia=ilock,ib=_ilock,ic=ied;
	for(int i=0;i<31;i++)
	{
		ulock[i]=ia%2;
		ia>>=1;
	}
	for(int i=0;i<31;i++)
	{
		_ulock[i]=ib%2;
		ib>>=1;
	}
	for(int i=0;i<31;i++)
	{
		ued[i]=ic%2;
		ic>>=1;
	}
}
void icalc()
{
	ilock=_ilock=ied=0;
	for(int i=30;i>=0;i--)
	{
		ilock<<=1;
		_ilock<<=1;
		ied<<=1;
		ilock|=ulock[i];
		_ilock|=_ulock[i];
		ied|=ued[i];
	}
}
void stf()
{
	ofstream fsave;
	fsave.open("SAVE.DAT",ofstream::out);
	fsave<<(int)finished<<endl;
	for(int i=0;i<SAV;i++)fsave<<sav[i]<<endl;
	icalc();
	fsave<<_ilock<<endl<<ilock<<endl<<ied<<endl;
	fsave.close();
}
void lff()
{
	ifstream fsave;
	fsave.open("SAVE.DAT",ifstream::in);
	fsave>>finished;
	for(int i=0;i<SAV;i++)fsave>>sav[i];
	fsave>>_ilock>>ilock>>ied;
	calc();
	fsave.close();
}
void bsod()
{
	ccls();
	ccolor("17");
	printpic(4);
	cpause(0);
	ccolor("07");
	ccls();
}
void play(int num)
{
	ccls();
	ccolor(text[num].cset);
	if(text[num].ed>=0)
	{
		printpic(14);
		for(int i=0;i<80;i++)cout<<'-';
		cout<<endl;
		if(!ued[text[num].ed])cout<<"*NEW*";
		cout<<pic[26].str[text[num].ed]<<endl;
		cout<<endl<<endl<<endl;
		for(int i=0;i<80;i++)cout<<'-';
		cout<<endl;
		return;
	}
	if(text[num].is_eoc)
	{
		printpic(14);
		for(int i=0;i<80;i++)cout<<'-';
		cout<<endl;
		if(text[num].chap>=0)cout<<"To be Continued in the next Chapter..."<<endl;
		else cout<<"Extra Chapter End"<<endl;
		cout<<endl<<endl<<endl;
		for(int i=0;i<80;i++)cout<<'-';
		cout<<endl;
		return;
	}
	if(text[num].is_bann)
	{
		printpic(14);
		for(int i=0;i<80;i++)cout<<'-';
		cout<<endl;
		if(text[num].chap>=0)
		{
			cout<<"Chapter "<<text[num].chap<<endl;
			cout<<pic[24].str[text[num].chap]<<endl;
		}
		else
		{
			cout<<"Extra "<<-text[num].chap<<endl;
			cout<<pic[25].str[-text[num].chap-1]<<endl;
		}
		cout<<endl<<endl;
		for(int i=0;i<80;i++)cout<<'-';
		cout<<endl;
		return;
	}
	printpic(text[num].pic);
	for(int i=0;i<80;i++)cout<<'-';
	cout<<endl;
	for(int i=0;i<text[num].len;i++)cout<<text[num].str[i]<<endl;
	for(int i=text[num].len;i<4;i++)cout<<endl;
	for(int i=0;i<80;i++)cout<<'-';
	cout<<endl;
	if(text[num].is_op)cout<<"[0,1,2]Select [S]Save [L]Load [C]Collections [T]Title [E]Exit"<<endl;
	else cout<<"[X]Continue [S]Save [L]Load [C]Collections [T]Title [E]Exit"<<endl;
}
void about()
{
	ccls();
	time_t rt;
	struct tm * tt;
	time(&rt);
	tt=localtime(&rt);
	//tm_mon==month-1
	if(tt->tm_mon==2&&tt->tm_mday==14)cout<<pic[21].str[0]<<endl;
	if(tt->tm_mon==3&&tt->tm_mday==26)cout<<pic[21].str[1]<<endl;
	if(tt->tm_mon==5&&tt->tm_mday==23)cout<<pic[21].str[2]<<endl;
	if(tt->tm_mon==6&&tt->tm_mday==3)cout<<pic[21].str[3]<<endl;
	if(tt->tm_mon==11&&tt->tm_mday==24)cout<<pic[21].str[4]<<endl;
	printpic(0);
	if(finished)printpic(1);
	printpic(2);
	cpause(1);
	ccls();
}
void dictd(int num)
{
	ccls();
	if(dict[num].len==0)
	{
		bsod();
		return;
	}
	printdic(num);
	cpause(1);
	ccls();
}
void dictm()
{
	beg:;
	ccls();
	ccolor("8E");
	printpic(5);
	int cho=system("choice /c 0123456789 /n")-1;
	if(cho==9)
	{
		ccls();
		return;
	}
	dictd(cho);
	goto beg;
}
void save(int num)
{
	beg:;
	ccls();
	for(int i=0;i<SAV;i++)
	{
		if(sav[i]==0)cout<<'['<<dat[i]<<']'<<"Empty"<<endl;
		else if(text[sav[i]].chap>=0)printf("[%c]Chapter %d:Frame %06d\n",dat[i],text[sav[i]].chap,sav[i]);
		else printf("[%c]Extra %d:Frame %06d\n",dat[i],-text[sav[i]].chap,sav[i]);
	}
	cout<<("["+dat.substr(SAV,1)+"]Exit")<<endl;
	int cho=system(("choice /n /c "+dat.substr(0,SAV+1)).c_str())-1;
	if(cho==SAV)
	{
		ccls();
		return;
	}
	if(sav[cho]>0)
	{
		if(!sure())goto beg;
	}
	sav[cho]=num;
	stf();
	ccls();
}
void load()
{
	beg:;
	ccls();
	for(int i=0;i<SAV;i++)
	{
		if(sav[i]==0)cout<<'['<<dat[i]<<']'<<"Empty"<<endl;
		else if(text[sav[i]].chap>=0)printf("[%c]Chapter %d:Frame %06d\n",dat[i],text[sav[i]].chap,sav[i]);
		else printf("[%c]Extra %d:Frame %06d\n",dat[i],-text[sav[i]].chap,sav[i]);
	}
	cout<<("["+dat.substr(SAV,1)+"]Exit")<<endl;
	int cho=system(("choice /n /c "+dat.substr(0,SAV+1)).c_str())-1;
	if(cho==SAV)
	{
		ccls();
		lasf=curf=0;
		return;
	}
	if(sav[cho]>0)
	{
		if(!sure())goto beg;
	}
	else
	{
		bsod();
		goto beg;
	}
	lasf=0;
	curf=sav[cho];
	ccls();
}
void init()
{
	ccls();
	system("mode 81,31");
	system("title Love a Mico Alpha 4");
	ifstream fdict,ftext,fpic;
	fpic.open("PIC.DAT",ifstream::in);
	while(1)
	{
		string s_len,s_name;
		int i_len,i_id;
		fpic>>s_len;
		if(s_len=="END")break;
		i_len=stoi(s_len,nullptr);
		fpic>>s_name>>i_id;
		fpic.get();
		pic[i_id].len=i_len;
		for(int i=0;i<i_len;i++)getline(fpic,pic[i_id].str[i]);
	}
	fpic.close();
	ccls();
	printpic(15);
	fdict.open("DICT.DAT",ifstream::in);
	while(1)
	{
		string s_len;
		int i_len,i_id;
		fdict>>s_len;
		if(s_len=="END")break;
		i_len=stoi(s_len,nullptr);
		fdict>>i_id;
		fdict.get();
		dict[i_id].len=i_len;
		for(int i=0;i<i_len;i++)getline(fdict,dict[i_id].str[i]);
	}
	fdict.close();
	ccls();
	printpic(16);
	int curchap;
	ftext.open("TEXT.DAT",ifstream::in);
	for(int j=1;;j++)
	{
		string s_len;
		int i_len,p_id;
		ftext>>s_len;
		if(s_len=="END")break;
		if(s_len=="TAG")
		{
			j--;
			int curtag;
			ftext>>curtag;
			tag[curtag]=j;
			continue;
		}
		if(s_len=="OPT")
		{
			text[j].is_op=1;
			text[j].chap=curchap;
			ftext>>text[j].pic;
			text[j].len=4;
			for(int i=0;i<3;i++)ftext>>text[j].targ[i];
			ftext.get();
			for(int i=0;i<4;i++)getline(ftext,text[j].str[i]);
			continue;
		}
		if(s_len=="GOTO")
		{
			j--;
			int curtag;
			ftext>>curtag;
			text[j].nxt=curtag;
			continue;
		}
		if(s_len=="ULK")
		{
			j--;
			int curtag;
			ftext>>curtag;
			text[j].ulk=curtag;
			continue;
		}
		if(s_len=="COL")
		{
			j--;
			string curtag;
			ftext>>curtag;
			text[j].cset=curtag;
			continue;
		}
		if(s_len=="CHAP")
		{
			ftext>>curchap;
			text[j].chap=curchap;
			chapbeg[curchap]=j;
			text[j].is_bann=1;
			text[j].len=1;
			continue;
		}
		if(s_len=="EOC")
		{
			text[j].chap=curchap;
			text[j].is_bann=1;
			text[j].is_eoc=1;
			text[j].len=1;
			continue;
		}
		if(s_len=="EOS")
		{
			text[j].chap=curchap;
			text[j].is_eos=1;
			text[j].len=1;
			continue;
		}
		if(s_len=="ED")
		{
			text[j].chap=curchap;
			ftext>>text[j].ed;
			text[j].len=1;
			continue;
		}
		if(s_len=="EDB")
		{
			j--;
			int curtag;
			ftext>>curtag;
			edbeg[curtag]=j;
			continue;
		}
		if(s_len=="REM")
		{
			j--;
			getline(ftext,svoid);
			continue;
		}
		text[j].chap=curchap;
		i_len=stoi(s_len,nullptr);
		ftext>>p_id;
		ftext.get();
		text[j].len=i_len;
		text[j].pic=p_id;
		for(int i=0;i<i_len;i++)getline(ftext,text[j].str[i]);
	}
	ftext.close();
	ccls();
	printpic(17);
	lff();
	ccls();
	ulock[0]=1;
	printpic(19);
	stf();
	ccls();
}
void col()
{
	beg:;
	ccls();
	ccolor("E1");
	printpic(23);
	int cho=system("choice /c ekpab /n");
	if(cho==1)
	{
		eds();
	}
	else if(cho==2)
	{
		dictm();
	}
	else if(cho==3)
	{
		
	}
	else if(cho==4)
	{
		
	}
	else
	{
		return;
	}
	goto beg;
}
void exec()
{
	beg:;
	ccls();
	if(text[curf].len==0)return;
	play(curf);
	ulock[text[curf].ulk]=1;
	stf();
	int cho;
	if(text[curf].ed>=0)
	{
		ued[text[curf].ed]=1;
		stf();
		cpause(1);
		return;
	}
	if(text[curf].is_op)goto opt;
	if(text[curf].is_bann)goto bann;
	cho=system("choice /c xslcte /n");
	if(cho==1)
	{
		lasf=curf;
		if(text[curf].nxt==0)curf++;
		else curf=tag[text[curf].nxt];
	}
	else if(cho==2)
	{
		save(curf);
	}
	else if(cho==3)
	{
		load();
	}
	else if(cho==4)
	{
		col();
	}
	else if(cho==5)
	{
		if(sure())return;
	}
	else
	{
		if(sure())exit(0);
	}
	goto beg;
	opt:;
	cho=system("choice /c 012slcte /n");
	if(cho==1)
	{
		lasf=curf;
		curf=tag[text[curf].targ[0]];
	}
	else if(cho==2)
	{
		lasf=curf;
		curf=tag[text[curf].targ[1]];
	}
	else if(cho==3)
	{
		lasf=curf;
		curf=tag[text[curf].targ[2]];
	}
	else if(cho==4)
	{
		save(curf);
	}
	else if(cho==5)
	{
		load();
	}
	else if(cho==6)
	{
		col();
	}
	else if(cho==7)
	{
		if(sure())return;
	}
	else
	{
		if(sure())exit(0);
	}
	goto beg;
	bann:;
	cpause(1);
	if(text[curf].is_eoc)
	{
		ulock[text[curf].chap+1]=1;
		stf();
		return;
	}
	lasf=curf;
	curf++;
	goto beg;
}
void eds()
{
	beg:;
	ccls();
	ccolor("35");
	for(int i=0;i<ED;i++)
	{
		if(ued[i])printf("[%c]%s\n",dat[i],pic[26].str[i].c_str());
		else cout<<"[?]????:????"<<endl;
	}
	cout<<("["+dat.substr(ED,1)+"]Exit")<<endl;
	int cho=system(("choice /n /c "+dat.substr(0,ED+1)).c_str())-1;
	if(cho==ED)
	{
		ccls();
		return;
	}
	if(ued[cho])
	{
		lasf=0;
		curf=edbeg[cho];
		ccls();
		exec();
		goto beg;
	}
	else
	{
		bsod();
		goto beg;
	}
}
void menuc()
{
	beg:;
	ccls();
	int curchar=0;
	for(;curchar<pic[24].len;curchar++)
	{
		if(ulock[curchar])cout<<'['<<dat[curchar]<<']'<<"Chapter "<<curchar<<":"<<pic[24].str[curchar]<<endl;
		else cout<<"[?]??????? ?"<<endl;
	}
	for(;curchar<pic[25].len+pic[24].len;curchar++)
	{
		if(ulock[pic[24].len-curchar-1])cout<<'['<<dat[curchar]<<']'<<"Extra "<<curchar-pic[24].len+1<<":"<<pic[25].str[curchar-pic[24].len]<<endl;
		else cout<<"[?]????? ?"<<endl;
	}
	cout<<'['<<dat[curchar]<<']'<<"Back"<<endl;
	int cho=system(("choice /n /c "+dat.substr(0,pic[24].len+pic[25].len+1)).c_str())-1;
	if(cho==curchar)return;
	if(cho<pic[24].len&&!ulock[cho])
	{
		bsod();
		goto beg;
	}
	if(cho>=pic[24].len&&!ulock[pic[24].len-cho-1])
	{
		bsod();
		goto beg;
	}
	if(cho>=pic[24].len)cho=pic[24].len-cho-1;
	lasf=0;
	curf=chapbeg[cho];
	exec();
	ccls();
}
void menu()
{
	beg:;
	ccls();
	ccolor("07");
	printpic(6);
	int cho=system("choice /c nlcae /n");
	if(cho==1)
	{
		menuc();
	}
	else if(cho==2)
	{
		load();
		exec();
	}
	else if(cho==3)
	{
		col();
	}
	else if(cho==4)
	{
		about();
	}
	else
	{
		ccls();
		printpic(6);
		if(sure())exit(0);
	}
	goto beg;
}
int main()
{
	init();
	menu();
}
