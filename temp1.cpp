#include <iostream>
using namespace std;

class temperature{
	
	double temp;
	char scale;
	
	public:
	
	double toC { 
		
		if( scale == 'C' ) return temp ;
		else if ( scale == 'K' ) return temp - 273.15;
		else if( scale == 'F' ) return (temp - 32.0) / 1.8 ;
		
		}
	
	
	
	};
	
	class table {
		
		unsigned int numstrok;
		unsigned int numstolb;
		double **temp=nullptr;
		
		public:
		
		
		};
	

int main ()
{ 
int com;

while(!com)
{ cout << "1 - Прочитать и вывести"<<endl
	   << "2 - Средняя температура по строке"<<endl
	   <<"3 - Минимальная температура по строке"<<endl
	   <<"4 - Сумма двух таблиц"<<endl
	   <<"5 - Максимальная температура для таблицы"<<endl
	   <<"0 -  Выход из программы"<<ednl;
	   cin>>com;
	switch(com)
	{
		case 1:
		 break;
		 
		 case 2:
        break;		 
		 
		 case 3:
		 break;
		 
		 case 4:
		 break;

         case 5:
         break;
		 
		default:
		 cout << "Такой команды нет в списке"<<endl;
		 
		}
		
	}

return 0;
}
 
