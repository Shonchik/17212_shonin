import java.io.FileWriter;
import java.util.List;

public class CSVWriter {

    public void run(List<Words> words) throws Exception {
        try (FileWriter writer = new FileWriter("2.csv", false)) {
            long word_count = 0;
            for (int i = 0; i < words.size(); ++i) {
                word_count += words.get(i).getCount();
            }
            for (int i = words.size() - 1; i >= 0; --i) {
                writer.write(words.get(i).getWord() + ";" + words.get(i).getCount() + ";" + ((double) words.get(i).getCount() / word_count) + "%" + "\n");
            }
        } catch (Exception e) {

            System.out.println(e.getMessage());
        }
    }
}