package util.db;

import java.sql.SQLException;


public class DBPool {
	//local 
	static MySqlInfo getLocalDB(String database) throws SQLException, ClassNotFoundException{
		return new MySqlInfo("localhost", 3306, "root", "abcd1234", database);
	}
}
