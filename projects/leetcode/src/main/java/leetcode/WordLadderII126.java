package leetcode;

import java.util.List;
import java.util.Set;

public class WordLadderII126 {
	/*
	 * 	Given two words (beginWord and endWord), and a dictionary's word list, 
	 *  find all shortest transformation sequence(s) from beginWord to endWord, such that:
		Only one letter can be changed at a time
		Each intermediate word must exist in the word list
		For example,
		
		Given:
		beginWord = "hit"
		endWord = "cog"
		wordList = ["hot","dot","dog","lot","log"]
		
		Return
		  [
		    ["hit","hot","dot","dog","cog"],
		    ["hit","hot","lot","log","cog"]
		  ]
		  
		Note:
		All words have the same length.
		All words contain only lowercase alphabetic characters
	 */
	
	public static List<List<String>> findLadders(String beginWord, String endWord, Set<String> wordList){
		//All words have the same length.
		//All words contain only lowercase alphabetic characters.
		//递归实现
		/*
		beginMidWordList
		*/
		return null;
////		System.out.println("beginWord: " + beginWord);
////		System.out.println("endWord: " + endWord);
//		List<List<String>> transformPathList = new ArrayList<List<String>>();
//		int len = beginWord.length();
//		//get begin index
//		int beginIndex = 0;
//		for (int i = 0 ; i < len; i ++){
//			if (beginWord.charAt(beginIndex) == endWord.charAt(beginIndex))
//				beginIndex ++;
//			else
//				break;
//		}
//		System.out.println(beginWord + "==>" + endWord + ":beginIndex: " + beginIndex);
//		
//		if (beginIndex >= len -1 ){
//			List<String> transformPath = new ArrayList<String>();
//			if (beginIndex == len)
//				transformPath.add(endWord);
//			else {
//				transformPath.add(beginWord);
//				transformPath.add(endWord);
//			}
//			transformPathList.add(transformPath);
//			System.out.println(transformPathList);
//			return transformPathList;
//		}
//		for (int i = beginIndex; i < len; i ++){
////			System.out.println("trying: " + i + "= " + beginWord.charAt(i) + "==>" + endWord.charAt(i));
//			for (int c ='a'; c <= 'z'; c ++){
////				if (c == )
////				String replaceLetter = Character.toString((char)c);
//				
//			}
////				Character.toString((char)c).length());
//			
//			
//			String middleWord = beginWord.replaceFirst(beginWord.substring(i, i + 1), endWord.substring(i, i + 1));
//			System.out.println(middleWord);
//			if (!wordList.contains(middleWord))
//				continue;
//			System.out.println(beginWord + "==>" + middleWord + "==>" + endWord);
//			List<List<String>> innerPathList = findLadders(middleWord, endWord, wordList);
//			if (innerPathList == null){
//				continue;
//			} else {
//				for (List<String> innerPath : innerPathList)
//					innerPath.add(0, beginWord);
//				transformPathList.addAll(innerPathList);
//			}
//		}
//		System.out.println();
//		return transformPathList;
	}
	
	public static void main(String[] args) {
//		String beginWord = "hit";
//		String endWord = "cog";
//		List<String> list = new ArrayList<String>(Arrays.asList("cot","dot","cit","lot","log"));
//		Set<String> wordList = new HashSet<String>(list);
//		System.out.println(findLadders(beginWord, endWord, wordList));
		
		
		
		
		
	}
}
