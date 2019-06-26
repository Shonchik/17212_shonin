import java.io.BufferedReader;

public class WordReader {
    private StringBuilder word;

    WordReader() throws Exception {
        try {
            word = new StringBuilder();
        } catch (Exception e) {
            System.err.println("ERROR with WordReader: " + e.getMessage());
            throw e;
        }
    }

    public String readWord(BufferedReader reader) throws Exception {
        try {
            word.setLength(0);
            int symbol = reader.read();
            while (-1 != symbol) {
                if (Character.isLetterOrDigit((char) symbol)) {
                    word.append((char) symbol);
                } else if (0 != word.length()) {
                    break;
                }
                symbol = reader.read();
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
            throw e;
        }
        return word.toString();
    }
}