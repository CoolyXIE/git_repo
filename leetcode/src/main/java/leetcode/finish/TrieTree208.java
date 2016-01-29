package leetcode.finish;

import java.util.ArrayList;
import java.util.List;

class TrieNode {
	char letter;
	TrieNode[] children;

	public TrieNode(char letter){
		this.letter = letter;
		children = new TrieNode[27];
	}

	public List<TrieNode> validChildren(char c){
		List<TrieNode> list = new ArrayList<TrieNode>();
		for (int i = 0; i < 26; i ++){
			if (children[i] != null && children[i].letter == c)
				list.add(children[i]);
		}
		return list;
	}

	public List<TrieNode> validChildren(){
		List<TrieNode> list = new ArrayList<TrieNode>();
		for (int i = 0; i < 26; i ++){
			if (children[i] != null)
				list.add(children[i]);
		}
		return list;
	}

}
public class TrieTree208 {
	TrieNode root;

	public TrieTree208() {
		root = new TrieNode('0');
	}

	public void insert(String word) {
		TrieNode parent = root;
		for (int i = 0; i < word.length(); i ++){
			char letter = word.charAt(i);
			int index = letter - 97;
			TrieNode node = parent.children[index];
			if (node != null && node.letter == letter){
				parent = parent.children[index];
				continue;
			}
			//not exists, create it!
			String subWord = word.substring(i);
			append(parent, subWord);
			return ;
		}

		if (parent.children[26] == null){
			parent.children[26] = new TrieNode('0');
		}
	}

	public boolean search(String word) {
		return find(word).equals("exact");
	}

	public boolean startsWith(String prefix) {
		return find(prefix).equals("prefix")||find(prefix).equals("exact");
	}

	private void append(TrieNode parent, String subWord) {
		for (int i = 0; i < subWord.length(); i ++){
			char letter = subWord.charAt(i);
			TrieNode newNode = new TrieNode(subWord.charAt(i));
			parent.children[letter-97] = newNode;
			parent = parent.children[letter-97];
		}
		parent.children[26] = new TrieNode('0');
	}

	private String find(String word){
		TrieNode parent = root;
		for (int i = 0; i < word.length(); i ++){
			char letter = word.charAt(i);
			if (parent.children[letter-97] == null)
				return "none";
			else 
				parent = parent.children[letter-97];
		}

		if (parent.children[26] != null)
			return "exact";
		else if (parent.validChildren().size() > 0)
			return "prefix";
		else return "none";
	}

}

