package shixi;

import java.util.Date;

abstract class Phone{
	long phoneNumber; 
	final int local_Call=1; 
	final int distance_Call=3; 
	final int international_Call=9; 
	double balance ; 
	boolean charge_Mode(int call_Mode) {
		return true;
	}
	double getBalance() {
		return balance;
	}
}

class MobilePhone extends Phone{
	String networkType;
}

class CommonMobilePhone extends MobilePhone{
	
}

class PersonalHandphoneSystem extends MobilePhone{
	
}

class FixedPhone extends Phone{
	double monthFee;
}

class CommonPhone extends FixedPhone{
	boolean longdistanceService; 
	boolean internationalService;
}

class IPPhone extends FixedPhone{
	boolean started; 
	Date expireDate;
}


public class Telephone {

}
