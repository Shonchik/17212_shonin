import org.apache.commons.io.FileUtils;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

class WordCounterTest {

    WordCounter counter = null;

    @BeforeEach
    void setUp() {
        try {
            counter = new WordCounter();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    @Test
    void run() {
        assertNotNull(counter);

        try {
            counter.run("src\\main\\java\\test.txt");
        }catch (Exception e){
            System.out.println(e);
        }

        try (BufferedReader fileReader = new BufferedReader(new FileReader("2.csv"))) {
            //String str = fileReader.readLine();
            assertTrue(FileUtils.contentEquals(new File("2.csv"), new File("test.csv")));
            //FileUtils.contentEquals("2.csv", "test.csv");

        } catch (Exception e) {
            System.err.println("ERROR: " + e.getMessage());
        }


    }
}