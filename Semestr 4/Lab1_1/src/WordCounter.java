import java.io.BufferedReader;
import java.io.FileReader;
import java.util.*;

public class WordCounter {
    private WordReader objReader;

    WordCounter() throws Exception {
        try {
            objReader = new WordReader();
        } catch (Exception e) {
            System.err.println("ERROR with WordCounter: " + e.getMessage());
            throw e;
        }
    }

    private void findCountWords(BufferedReader fileReader, Map<String, Integer> mapWords) throws Exception {
        try {
            String word = objReader.readWord(fileReader);
            while (0 != word.length()) {
                mapWords.merge(word, 1, (a, b) -> a + b);
                word = objReader.readWord(fileReader);
            }
        } catch (Exception e) {
            System.err.println("ERROR with findCountWords: " + e.getMessage());
            throw e;
        }
    }

    private void sortWords(List<Words> sortedWords, Map<String, Integer> mapWords) throws Exception {
        try {
            for (Map.Entry<String, Integer> obj : mapWords.entrySet()) {
                Words word = new Words(obj.getKey(), obj.getValue());
                sortedWords.add(word);
            }
            Collections.sort(sortedWords);
        } catch (Exception e) {
            System.err.println("ERROR with sortWords " + e.getMessage());
            throw e;
        }
    }

    public void run(String fileName) throws Exception {
        try (BufferedReader fileReader = new BufferedReader(new FileReader(fileName))) {

            Map<String, Integer> mapWords = new HashMap<String, Integer>();
            findCountWords(fileReader, mapWords);
            List<Words> sortedWords = new ArrayList<Words>();
            sortWords(sortedWords, mapWords);
            CSVWriter writer = new CSVWriter();
            writer.run(sortedWords);

        } catch (Exception e) {
            System.err.println("ERROR with run: " + e.getMessage());
            throw e;
        }
    }
}