#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include "clsDate.h"

using namespace std;


class clsQueueLine
{
private:

	short _TotalTickets = 0;
	short _AverageServeTime = 0;
	string _Prefix = "";
	class  clsTickets
	{
	private:
		short _TotalTickets=0;
		string _Prefix="";
		short _AverageServeTime = 0;
		short _Number = 0;
		short _WaitingClients = 0;
		short _ExpectedServeTime = 0;
		string _TicketTime;
	public:
		clsTickets(string Prefix, short Number, short WaitingClients, short AverageServeTime)
		{
			_Number = Number;
			_Prefix = Prefix;
			_WaitingClients = WaitingClients;
			_AverageServeTime = AverageServeTime;
			_TicketTime = clsDate::GetSystemDateTimeString();
		}
		string Prefix()
		{
			return _Prefix;
		}

		short Number()
		{
			return _Number;
		}

		string FullNumber()
		{
			return _Prefix + to_string(_Number);
		}

		string TicketTime()
		{
			return _TicketTime;
		}

		short WaitingClients()
		{
			return _WaitingClients;
		}

		short ExpectedServeTime()
		{
			return _AverageServeTime * WaitingClients();
		}

		void Print()
		{
			cout << "\n\t\t\t  _______________________\n";
			cout << "\n\t\t\t\t    " << FullNumber();
			cout << "\n\n\t\t\t    " << _TicketTime;
			cout << "\n\t\t\t    Wating Clients = " << _WaitingClients;
			cout << "\n\t\t\t      Serve Time In";
			cout << "\n\t\t\t       " << ExpectedServeTime() << " Minutes.";
			cout << "\n\t\t\t  _______________________\n";
		}
	};
public:
	queue <clsTickets> QueueLine;
	clsQueueLine(string Prefix, short AverageServceTime)
	{
		_Prefix = Prefix;
		_AverageServeTime = AverageServceTime;
	}
	void IssueTicket()
	{
		_TotalTickets++;
		clsTickets Ticket(_Prefix, _TotalTickets, WaitingClients(), _AverageServeTime);
		QueueLine.push(Ticket);
	}
	int WaitingClients()
	{
		return QueueLine.size();
	}
	short ServedClients()
	{
		return _TotalTickets - WaitingClients();
	}

	void PrintInfo()
	{
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t\tQueue Info";
		cout << "\n\t\t\t _________________________\n";
		cout << "\n\t\t\t    Prefix   = " << _Prefix;
		cout << "\n\t\t\t    Total Tickets   = " << _TotalTickets;
		cout << "\n\t\t\t    Served Clients  = " << ServedClients();
		cout << "\n\t\t\t    Wating Clients  = " << WaitingClients(); ;
		cout << "\n\t\t\t _________________________\n";
		cout << "\n";
	}

	void PrintRicketsLineRTL()
	{
	if (QueueLine.empty())
		cout << "\n\t\tTickets: No Tickets.";
	else
	{
		cout << "\n\t\tTickets: ";
		queue<clsTickets>TempQueueLine = QueueLine;
		while (!TempQueueLine.empty())
		{
			clsTickets Ticket = TempQueueLine.front();
			cout << " " << Ticket.FullNumber() << " <-- ";
			TempQueueLine.pop();
		}
		cout << "\n";
	}
	}

	void PrintRicketsLineLTR()
	{
		if (QueueLine.empty())
			cout << "\n\t\tTickets: No Tickets.";
		else
		{
			cout << "\n\t\tTickets: ";
			queue<clsTickets> TempQueueLine = QueueLine;
			stack <clsTickets> TempStackLine;
			while (!TempQueueLine.empty())
			{
				TempStackLine.push(TempQueueLine.front());
				TempQueueLine.pop();
			}
			while (!TempStackLine.empty())
			{
				clsTickets Ticket = TempStackLine.top();
				cout << " " << Ticket.FullNumber() <<" --> ";
				TempStackLine.pop();
			}
			cout << "\n";
		}
	}

	void PrintAllTickets()
	{
		cout << "\n\n\t\t\t       ---Tickets---";

		if (QueueLine.empty())
			cout << "\n\n\t\t\t     ---No Tickets---\n";

		//we copy the queue in order not to lose the original
		queue <clsTickets> TempQueueLine = QueueLine;


		while (!TempQueueLine.empty())
		{
			TempQueueLine.front().Print();
			TempQueueLine.pop();
		}
	}
	bool ServeNextClient()
	{
		if (QueueLine.empty())
			return false;
		QueueLine.pop();
		return true;
	}
};

