package leetcode;

import java.util.ArrayList;
import java.util.List;



public class WordDictionary221 {

	Node root = new Node('0');

	public void addWord(String word){
		Node parent = root;
		out:for (int i = 0; i < word.length(); i ++){
			char letter = word.charAt(i);
			for (int j = 0; j < 26; j ++){
				Node node = parent.children[j];
				if (node != null && node.letter == letter){
					parent = parent.children[j];
					continue out;
				}
			}
			//not exists, create it!
			String subWord = word.substring(i);
			insert(parent, subWord);
			return ;
		}
	}

	private void insert(Node parent, String subWord) {
		for (int i = 0; i < subWord.length(); i ++){
			char letter = subWord.charAt(i);
			Node newNode = new Node(subWord.charAt(i));
			parent.children[letter-97] = newNode;
			parent = parent.children[letter-97];
		}
	}
	
	public boolean searchWord(String word){
		if (!word.contains(".")){
			Node parent = root;
			for (int i = 0; i < word.length(); i ++){
				char letter = word.charAt(i);
				if (parent.children[letter-97] == null)
					return false;
				else 
					parent = parent.children[letter-97];
			}
			return true;
		} else{
			List<Node> parents = new ArrayList<Node>();
			parents.add(root);
			for (int i = 0; i < word.length(); i ++){
				char letter = word.charAt(i);
				int size = parents.size();
				if (size == 0)
					return false;
				int index = 0;
				for (int count = 0; count < size; count ++){
					if (!parents.get(index).validChildren(letter).isEmpty())
						parents.addAll(parents.get(index).validChildren(letter));
					if (letter != '.')
						parents.remove(0);
					else
						index ++;
				}	
			}
			return true;
		}
	}
		
	
	public static void main(String[] args){
		WordDictionary221 dict = new WordDictionary221();
		dict.addWord("a");
		dict.addWord("a");
		System.out.println(dict.searchWord(".a"));
		System.out.println(dict.searchWord("a."));
		
		
	}
}
class Node{
	char letter;
	Node[] children;

	public Node(char letter){
		this.letter = letter;
		children = new Node[26];
	}
	
	public List<Node> validChildren(char c){
		List<Node> list = new ArrayList<Node>();
		for (int i = 0; i < 26; i ++){
			if (children[i] != null){
				if (c == '.')
					list.add(children[i]);
				else
					if (children[i].letter == c)
						list.add(children[i]);
			}
		}
		return list;
	}
}
