import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.FileReader;

import static org.junit.jupiter.api.Assertions.*;

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
            counter.run("src\\test.txt");
        }catch (Exception e){
            System.out.println(e);
        }

        try (BufferedReader fileReader = new BufferedReader(new FileReader("2.csv"))) {
            String str = fileReader.readLine();

            assertTrue(str.equals("odin;1;1.0%"));

        } catch (Exception e) {
            System.err.println("ERROR: " + e.getMessage());
        }


    }
}