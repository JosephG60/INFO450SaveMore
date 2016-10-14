//
//  main.cpp
//  SaveMoreApp
//
//  Created by Joseph Gay on 10/13/16.
//  Copyright © 2016 Joseph Gay. All rights reserved.
//

#include <iostream>
#include <ctime>

struct date
{
    int d,m,y; //delete
};

class account
{
    int ac_no;
    date creation; //delete
    float rate;
    float bal;

public:
    account()
    {
        ac_no = generateAcNo(); //delete
        creation = getSystemDate(); //delete
        rate = 0;
        bal = 0;
    }
    
    account(int a, date c, float r, float b)
    {
        ac_no = a;
        creation = c;
        rate = r;
        bal = b;
    }
    
    void setDate(date d) //delete
    {
        creation.d = d.d;
        creation.m = d.m;
        creation.y = d.y;
    }
    
    date getDate()
    {
        return d; //delete
    }
    
    void setAccountNumber(int acno)
    {
        ac_no = acno;
    }
    
    int getAccountNumber()
    {
        return ac_no;
    }
    
    void setAccountRate(float r)
    {
        rate = r;
    }
    
    float getAccountRate()
    {
        return rate;
    }
    
    void setBalance(float b)
    {
        bal = b;
    }
    
    float getBalance()
    {
        return bal;
    }
    
    bool withdraw(float b)
    {
        if (bal < b)
            return false;
        
        bal = bal - b;
        
        return true;
    }
    
    void deposit(float b)
    {
        bal = bal + b;
    }
    
    void display()
    {
        std::cout<<"Account Number: "<<ac_no<<std::endl;
        std::cout<<"Interest Rate: "<<rate<<std::endl;
        std::cout<<"Balance: "<<bal<<std::endl;
    }
};

class Savings:public account
{

public:
    void setRate()
    {
        float bal = getBalance();
        
        if (bal < 10000)
        {
            account::setAccountRate(1);
        }
        else
        {
            account::setAccountRate(2);
        }
    }
    
    void setBalance(float b)
    {
        account::setBalance(b);
        setAccountRate();
    }
    
    bool withdraw(float b)
    {
        b = account::withdraw(b);
        b = account::withdraw(2);
        return b;
    }
};

class Checking:public account
{
public:
    void setBalance(float b)
    {
        account::setBalance(b);
        if (getAccountRate() < 500)
            account::withdraw(5);
    }
    
    bool withdraw(float b)
    {
        if (account::withdraw(b))
        {
            if (getAccountRate() < 500)
                return account::withdraw(5);
        }
        return false;
    }
};

class CD:public account
{
    int term;

public:
    CD(int a, date c, float r, float b, int t):account(a, c, r, b)
    {
        term = t;
        update();
    }
    
    void update()
    {
        if (term < 5)
        {
            account::setAccountRate(5);
        }
        else
        {
            account::setAccountRate(10);
        }
    }
    
    bool withdraw(float b)
    {
        if (getSystemDate() - getDate() < term)
        {
            float w = 10 * getBalance() / 100;
            account::withdraw(w);
        }
        return account::withdraw(b);
    }
};

int main()
{
    Savings ac1;
    ac1.setBalance(10000);
    ac1.setRate();
    
    Checking ac2;
    ac2.setBalance(600);
    
    CD ac3(100, getSystemDate(), 0, 10000, 3);
    
    ac1.display();
    ac2.display();
    ac3.display();
    
    ac2.withdraw(200);
    ac1.withdraw(1000);
    ac3.withdraw(2000);
}
