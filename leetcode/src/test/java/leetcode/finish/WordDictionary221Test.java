package leetcode.finish;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import junit.framework.TestCase;
import leetcode.WordDictionary221;
import tool.FileHelper;

public class WordDictionary221Test extends TestCase {
	static List<String> addWordList = new ArrayList<String>();
	static List<String> searchWordList = new ArrayList<String>();
	
	private WordDictionary221 dict = new WordDictionary221();
	
	public WordDictionary221Test() throws IOException{
		parseFile(Conf.LEETCODE_BASIC_DIR + "221.txt");
	}

	public void testSearchWord() {
		for (String word : addWordList){
			dict.addWord(word);
		}
		
		assertEquals(false, dict.searchWord("vanilla.dehyde"));
		
	}
	
	public static String parse(String source){
		int begin = source.indexOf('(') + 2;
		int end = source.length() - 2;
		return source.substring(begin, end);
	}
	
	public static void parseFile(String filePath) throws IOException{
		BufferedReader br = FileHelper.readFile(filePath);
		String line = br.readLine();
		String[] sources = line.split(",");
		System.out.println(sources.length);
		for (String source : sources){
			if (source.contains("addWord("))
				addWordList.add(parse(source));
			else if (source.contains("search("))
				searchWordList.add(parse(source));
		}
		br.close();
	}

}
