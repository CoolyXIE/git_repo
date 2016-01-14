package aribnb;

import java.text.ParseException;
import java.util.Date;

public class User {
	String id;
	Date dateAccountCreated;
	Date timeFirstActive;
	Date dateFirstBooking;
	String gender;
	int age;
	SignupMethod signupMethod;
	Language language;
	AffiliateProvider affiliateProvider;
	SignupApp signupApp;
	FirstDeviceType firstDeviceType;
	FirstBrowser firstBrowser;
	CountryDestination countryDestination;

	public User(String id, Date dateAccountCreated, Date timeFirstActive,
			Date dateFirstBooking, String gender, int age,
			SignupMethod signupMethod, Language language,
			AffiliateProvider affiliateProvider, SignupApp signupApp,
			FirstDeviceType firstDeviceType, FirstBrowser firstBrowser,
			CountryDestination countryDestination) {
		super();
		this.id = id;
		this.dateAccountCreated = dateAccountCreated;
		this.timeFirstActive = timeFirstActive;
		this.dateFirstBooking = dateFirstBooking;
		this.gender = gender;
		this.age = age;
		this.signupMethod = signupMethod;
		this.language = language;
		this.affiliateProvider = affiliateProvider;
		this.signupApp = signupApp;
		this.firstDeviceType = firstDeviceType;
		this.firstBrowser = firstBrowser;
		this.countryDestination = countryDestination;
	}

	public static User parse(String line) throws ParseException{
		String[] info = line.split(",");
		String id = info[0];
		Date dateAccountCreated =  Conf.shortDateFormat.parse(info[1]);
		Date timeFirstActive = Conf.longDateFormat.parse(info[2]);
		Date dateFirstBooking = Conf.shortDateFormat.parse(info[3]);
		String gender = info[4];
		int age = (info[5].isEmpty())?-1:Integer.parseInt(info[5]);
		SignupMethod signupMethod = SignupMethod.valueOf(info[6]);
		Language language = Language.valueOf(info[8]);
		AffiliateProvider affiliateProvider = AffiliateProvider.valueOf(info[10]);
		SignupApp signupApp = SignupApp.valueOf(info[12]);
		FirstDeviceType firstDeviceType = FirstDeviceType.valueOf(info[13]);
		FirstBrowser firstBrowser = FirstBrowser.valueOf(info[14]);
		CountryDestination countryDestination = CountryDestination.valueOf(info[15]);

		User user = new User(id, dateAccountCreated, timeFirstActive, dateFirstBooking, gender, age, signupMethod, language, affiliateProvider, signupApp, firstDeviceType, firstBrowser, countryDestination);

		return user;
	}
}

enum SignupMethod {
	goolge, facebook, basic, unknown;
}

enum Language{
	hr,	zh,	ca,	tr,	no,	hu,	th,	de,	id,	fi,	fr,	sv,	is,
	da,	it,	ko,	cs,	el,	pl,	pt,	en,	ru,	es,	ja,	nl, unknown;
}

enum AffiliateProvider{
	direct,	google,	other,	meetup,	padmapper,	wayn,	bing,
	gsp,	daum,	baidu,	facebook_open_graph, email_marketing,
	naver,	yandex,	facebook,	vast,	craigslist, 	yahoo, unknown;
}

enum SignupApp{
	Android,
	Web,
	unknown,
	Moweb,
	iOS;
}

enum FirstDeviceType{
	iPad,
	Android_Tablet,
	iPhone,
	Mac_Desktop,
	Android_Phone,
	Windows_Desktop,
	Unknown,
	Desktop_Other,
	first_device_type,
	SmartPhone_Other;
}

enum FirstBrowser{
	RockMelt,
	Avant_Browser,
	Sogou_Explorer,
	Stainless,
	Arora,
	Chrome,
	Outlook_2007,
	SiteKiosk,
	Mozilla,
	Safari,
	IE,
	Silk,
	Chromium,
	Android_Browser,
	Flock,
	SeaMonkey,
	Opera_Mobile,
	Firefox,
	PS_Vita_browser,
	wOSBrowser,
	Mobile_Safari,
	Pale_Moon,
	Camino,
	Iron,
	Conkeror,
	Kindle_Browser,
	Chrome_Mobile,
	Maxthon,
	CometBird,
	Mobile_Firefox,
	BlackBerry_Browser,
	Crazy_Browser,
	TenFourFox,
	IE_Mobile,
	Google_Earth,
	Googlebot,
	IceDragon,
	Palm_Pre_web_browser,
	Opera,
	Comodo_Dragon,
	IceWeasel,
	Opera_Mini,
	Apple_Mail,
	Yandex_Browser,
	NetNewsWire,
	CoolNovo,
	unknown,
	TheWorld_Browser,
	OmniWeb,
	Epic,
	AOL_Explorer,
	SlimBrowser;
}

enum CountryDestination{
	US,
	other,
	AU,
	GB,
	CA,
	IT,
	NDF,
	PT,
	FR,
	ES,
	NL,
	unknown,
	DE;
}