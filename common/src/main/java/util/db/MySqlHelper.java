package util.db;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

public class MySqlHelper {
	private Connection connection;
	private Statement st;
	//constructor
	public MySqlHelper(MySqlInfo mySqlInfo) throws ClassNotFoundException, SQLException {
		Class.forName("com.mysql.jdbc.Driver");
		connection = DriverManager.getConnection(mySqlInfo.getUrl(), mySqlInfo.getUser(), mySqlInfo.getPasswd());
		st = connection.createStatement();
	}
	
	//query
	public ResultSet query(String mySqlCmd) throws SQLException{
		return st.executeQuery(mySqlCmd);
	}
	
	//insert 
	public int update(String sqlCmd) throws SQLException{
		System.out.println(sqlCmd);
		return st.executeUpdate(sqlCmd);
	}
	
	public int insert(String table, Map<String, String> map) throws SQLException{
		String sql = "INSERT INTO " + table;
		String keys = "";
		String values = "";
		for(Entry<String, String> entry:map.entrySet()){
			keys += "," + entry.getKey();
			values += "," + entry.getValue();
		}
		keys = "(" + keys.substring(1) + ")";
		values = "(" + values.substring(1) + ")";
		sql += keys + " VALUES" + values;
		return update(sql);
	}
	
	public int replace(String table, Map<String, String> map) throws SQLException{
		String sql = "REPLACE INTO " + table;
		String keys = "";
		String values = "";
		for(Entry<String, String> entry:map.entrySet()){
			keys += "," + entry.getKey();
			values += "," + entry.getValue();
		}
		keys = "(" + keys.substring(1) + ")";
		values = "(" + values.substring(1) + ")";
		sql += keys + " VALUES" + values;	
		return update(sql);
	}
	
	//close
	public void close() throws SQLException{
		st.close();
		connection.close();
	}
	
	public static void main(String[] args) throws ClassNotFoundException, SQLException {
		MySqlHelper mySql = new MySqlHelper(DBPool.getLocalDB("university"));
		Map<String, String> map = new HashMap<String, String>();
		map.put("name", "'Geodynamics'");
		map.put("teacher_id", "'A11'");
		mySql.insert("courses", map);
		mySql.close();
	}
}


