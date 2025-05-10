#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
//#include<algorithm>
using namespace std;

struct client
{
    string name;
    string pin;
    string phnumber;
    string accbalance;
    string accnumber;
};
vector<string> data_fromfile();
vector<client>vector_clientslist(vector<string>vec);
void play();
//---------------add client from user to file
client struct_addnewclient()
{
    vector<client>fromfile;
    fromfile = vector_clientslist(data_fromfile());
    client val;
    bool q = false;
    cout << "enter account number : ";
    getline(cin >> ws, val.accnumber);
    for (int i = 0; i < fromfile.size(); i++)
    {
        if (val.accnumber == fromfile[i].accnumber)
        {
            q = true;
        }
    }
    if (q == true)
    {
        cout << "it is here " << endl;
        return struct_addnewclient();
    }
    cout << "enter name : ";
    getline(cin, val.name);
    cout << "enter phone number : ";
    getline(cin, val.phnumber);
    cout << "enter pin number : ";
    getline(cin, val.pin);
    cout << "enter account balance : ";
    getline(cin, val.accbalance);
    return val;
}

vector<client>vector_newclients()
{
    vector<client>data;
    data.push_back(struct_addnewclient());

    return data;
}

void data_fromuser_uptofile(vector<client>data, string dil = "#//#")
{
    vector<client>dd;
    dd = data;
    //bool t = false;
    //cout << "enter account number :";
    //string f;
    //getline(cin >> ws, f);

    //for (int s = 0; s < dd.size(); s++)
    //{
    //    if (dd[s].accnumber == f)
    //    {
    //        t = true;
    //    }
    //}
    //if (t = true)
    //{
    //    cout << "already here " << endl;
    //    data_fromuser_uptofile(dd);
    //}
    fstream file;
    string h = "";
    file.open("clientdata.txt", ios::app);
    for (client& n : data)
    {
        h += n.accnumber + dil;
        h += n.name + dil;
        h += n.phnumber + dil;
        h += n.pin + dil;
        h += n.accbalance;
        file << h;
        file << endl;
        h = "";
    }
    file.close();
}
//---------------------------------

//-----------------take data from file
vector<client>vector_clientslist(vector<string>vec)
{
    vector<client>clent;
    client ss;
    int i = 0;
    while(vec.size()>0)
    {
        ss.accnumber = vec[i];
        ss.name = vec[i+1];
        ss.phnumber = vec[i+2];
        ss.pin = vec[i+3];
        ss.accbalance = vec[i+4];
        vec.erase(vec.begin() + 0, vec.begin() + 5);
        clent.push_back(ss);
    }
    return clent;
}

vector<string> data_fromfile()
{
    string c = "#//#";
    vector<string>clientt;
    fstream file;
    file.open("clientdata.txt", ios::in);
    string data;
    while (getline(file, data))
    {
        string h = "";
        int x = data.find("#//#");
        while (x > 0)
        {
            for (int i = 0; i < x; i++)
            {
                h += data[i];
            }
            clientt.push_back(h);
            h = "";
            data.erase(0, x+c.length());
            x = data.find(c);
        }
        h = data;
        clientt.push_back(h);
    }
    file.close();
    return clientt;
}
//----------------

void update_data_sendtofile(vector<client>vec,string dil="#//#")
{
    fstream file;
    string h;
    file.open("clientdata.txt", ios::out);
    h += vec[0].accnumber + dil;
    h += vec[0].name + dil;
    h += vec[0].phnumber + dil;
    h += vec[0].pin + dil;
    h += vec[0].accbalance;
    file << h;
    file << endl;
    h = "";
    file.close();
    file.open("clientdata.txt", ios::app);
    for (int i = 1; i < vec.size(); i++)
    {
        h += vec[i].accnumber + dil;
        h += vec[i].name + dil;
        h += vec[i].phnumber + dil;
        h += vec[i].pin + dil;
        h += vec[i].accbalance;
        file << h;
        file << endl;
        h = "";
    }
    file.close();
}

vector<client>delete_client(vector<client>vecc)
{
    vector<client>dc;
    string fin;
    bool t = false;
    while (t == false)
    {
        cout << "enter account number of client: ";
        cin >> fin;
        for (int i = 0; i < vecc.size(); i++)
        {
            if (fin == vecc[i].accnumber)
            {
                t = true;
                continue;
            }
            else
            {
                dc.push_back(vecc[i]);
            }
        }
        if (t == false)
        {
            cout << "not here " << endl;
        }
    } 
    update_data_sendtofile(dc);
    return dc;
}

client struct_update_client(string ss)
{
    client val;
    val.accnumber = ss;
    cout << "enter name : ";
    getline(cin>>ws, val.name);
    cout << "enter phone number : ";
    getline(cin, val.phnumber);
    cout << "enter pin number : ";
    getline(cin, val.pin);
    cout << "enter account balance : ";
    getline(cin, val.accbalance);
    return val;
}

vector<client>update_client(vector<client>vecc)
{
    vector<client>up;
    vector<client>old;
    old = vecc;
    bool t=false;
    cout << "enter account number of client :";
    string n;
    cin >> n;
    for (int i = 0; i < vecc.size(); i++)
    {
        if (vecc[i].accnumber == n)
        {
            t = true;
            for (client& s : vecc)
            {
                if (s.accnumber == n)
                {
                    up.push_back(struct_update_client(n));
                }
                else
                    up.push_back(s);
            }
            update_data_sendtofile(up);
        }
    }
    if (t==false)
    {
        cout << "not here" << endl;
        return update_client(old);
    }
    return up;
}

void showclients_list()
{
    vector<string>data;
    vector<client>st_vectordata;
    data = data_fromfile();
    st_vectordata = vector_clientslist(data);

    printf("                  clients list (%d) client", st_vectordata.size());
    cout << endl;
    cout << endl;
    cout << left << setw(15) << "|name" << setw(20) << "|account number"
        << setw(15) << "|phone number" << setw(15) << "|pin code" <<
        setw(15) << "|account balance";
    cout << endl;

    for (int i = 0; i < st_vectordata.size(); i++)
    {
        cout << left << setw(15) << st_vectordata[i].name << setw(20) << st_vectordata[i].accnumber
            << setw(15) << st_vectordata[i].phnumber << setw(15) << st_vectordata[i].pin <<
            setw(15) << st_vectordata[i].accbalance;
        cout << endl;
    }
}

void deposit()
{
    bool t=true;
    string acc;
    int s;
    int sac;
    cout << "enter account number :";
    cin >> acc;
    vector<client>data;
    data = vector_clientslist(data_fromfile());
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].accnumber == acc)
        {
            cout << " there are client details " << endl;
            cout << "account number :" << data[i].accnumber << endl;
            cout << "name :" << data[i].name << endl;
            cout << "pin code :" << data[i].pin << endl;
            cout << "phone number :" << data[i].phnumber << endl;
            cout << "account balance :" << data[i].accbalance << endl;
            cout << "enter deposit amount : ";
            cin >> s;
            sac = stoi(data[i].accbalance);
            data[i].accbalance = to_string(sac + s);
            t = true;
            break;
        }
        else
            t = false;
    }
    if (t == false)
    {
        cout << "not here " << endl;
        deposit();
    }
    update_data_sendtofile(data);
}

void withdraw()
{
    bool t = true;
    string acc;
    int s;
    int sac;
    cout << "enter account number :";
    cin >> acc;
    vector<client>data;
    data = vector_clientslist(data_fromfile());
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].accnumber == acc)
        {
            cout << " there are client details " << endl;
            cout << "account number :" << data[i].accnumber << endl;
            cout << "name :" << data[i].name << endl;
            cout << "pin code :" << data[i].pin << endl;
            cout << "phone number :" << data[i].phnumber << endl;
            cout << "account balance :" << data[i].accbalance << endl;
            
            
            sac = stoi(data[i].accbalance);
            int nn = 1;
            while (nn > 0)
            {
                cout << "enter withdraw amount : ";
                cin >> s;
                if (s < sac)
                {
                    data[i].accbalance = to_string(sac - s);
                    nn = -1;
                }
                else
                {
                    cout << "amount exceeds the balance , you can draw up to " << sac << endl;
                }
            }
            t = true;
            break;
        }
        else
            t = false;
    }
    if (t == false)
    {
        cout << "not here " << endl;
        deposit();
    }
    update_data_sendtofile(data);
}

void totalbalance()
{
    vector<client>data;
    data= vector_clientslist(data_fromfile());
    cout << left << setw(15) << "|name" << setw(20) << "|account number" <<
        setw(15) << "|account balance";
    cout << endl;
    for (client& s : data)
    {
        cout << left << setw(15) << s.name << setw(20) << s.accnumber<<
            setw(15) << s.accbalance;
        cout << endl;
    }
}

void goback()
{
    cout << "press to go back" << endl;
    system("pause>0");
    play();
}

void transaction()
{
    cout << "[1] deposit" << endl;
    cout << "[2] withdraw" << endl;
    cout << "[3] total balance" << endl;
    cout << "[4] main menu" << endl;
    int n;
    cin >> n;
    switch (n)
    { 
    case(1):system("cls");
        deposit();
        transaction();
        break;
    case(2):system("cls");
        withdraw();
        transaction();
        break;
    case(3):system("cls");
        totalbalance();
        transaction();
        break;
    case(4):system("cls");
        goback();
        break;
    }
    
}

void play()
{
    vector<string>data;
    vector<client>st_vectordata;
    data = data_fromfile();
    st_vectordata = vector_clientslist(data);

    int n;
    cout << "[1] show client list " << endl;
    cout << "[2] delete client " << endl;
    cout << "[3] update client info " << endl;
    cout << "[4] add new client " << endl;
    cout << "[5] transactions" << endl;
    cout << "[6] exit" << endl;
    cin >> n;

        system("cls");
        switch (n)
        {
        case(1):showclients_list();
            goback();
            break;
        case(2):delete_client(st_vectordata);
            goback();
            break;
        case(3):update_client(st_vectordata);
            goback();
            break;
        case(4):data_fromuser_uptofile(vector_newclients());
            goback();
            break;
        case(5):transaction();
            
            break;
        case(6): break;
        }
}

int main()
{
    play();
    return 0;
}