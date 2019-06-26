import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class SqrtTest {

    private Context context;
    private List<String> arg;
    private CommandClass obj = null;



    @Test
    void run() {

        try {
            Factory.createCommand(Arrays.asList("define", "a", "1")).run();
            Factory.createCommand(Arrays.asList("define", "b", "2")).run();
            Factory.createCommand(Arrays.asList("define", "c", "1")).run();

            Factory.createCommand(Arrays.asList("push", "2")).run();
            Factory.createCommand(Arrays.asList("push", "a")).run();
            Factory.createCommand(Arrays.asList("*")).run();

            Factory.createCommand(Arrays.asList("push", "b")).run();
            Factory.createCommand(Arrays.asList("push", "0")).run();
            Factory.createCommand(Arrays.asList("-")).run();

            Factory.createCommand(Arrays.asList("push", "a")).run();
            Factory.createCommand(Arrays.asList("push", "c")).run();
            Factory.createCommand(Arrays.asList("*")).run();
            Factory.createCommand(Arrays.asList("push", "4")).run();
            Factory.createCommand(Arrays.asList("*")).run();

            Factory.createCommand(Arrays.asList("push", "b")).run();
            Factory.createCommand(Arrays.asList("push", "b")).run();
            Factory.createCommand(Arrays.asList("*")).run();

            Factory.createCommand(Arrays.asList("-")).run();

            Factory.createCommand(Arrays.asList("sqrt")).run();

            Factory.createCommand(Arrays.asList("+")).run();

            Factory.createCommand(Arrays.asList("/")).run();
            Field f = Factory.class.getDeclaredField("context");
            f.setAccessible(true);
            assertEquals(-1.0, ((Context)f.get(null)).popFromStack());
            f.setAccessible(false);
        }catch(Exception e){
            System.out.println("ERROR in TEST: " + e);
        }
    }
}