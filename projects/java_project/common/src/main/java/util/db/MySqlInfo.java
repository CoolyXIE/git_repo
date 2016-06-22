package util.db;

public class MySqlInfo{
	private String host;
	private int port;
	private String user;
	private String passwd;
	private String database;
	
	public MySqlInfo(String host, int port, String user, String passwd, String database) {
		super();
		this.host = host;
		this.port = port;
		this.user = user;
		this.passwd = passwd;
		this.database = database;
	}

	public String getUrl() {
		return "jdbc:mysql://" + host + ":" + port +"/" + database;
	}

	public String getUser() {
		return user;
	}

	public String getPasswd() {
		return passwd;
	}
	
}