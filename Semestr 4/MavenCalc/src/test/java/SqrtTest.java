import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class SqrtTest {

    private Context context;
    private List<String> arg;
    private CommandClass obj = null;

    @BeforeEach
    void setUp() {
        try {
            context = new Context();
            arg = new ArrayList<>();
            obj = new Sqrt();
            context.pushToStack(16.0);
            arg.add("sqrt");

            Class<?> className = Class.forName(obj.getClass().getName());

            //Получаю список полей класса и начинаю их обход
            Field[] declaredFields = className.getDeclaredFields();
            for (Field declaredField : declaredFields) {
                //Делаю поле доступным
                declaredField.setAccessible(true);
                //Если аннотация класса Inject, то
                if (declaredField.isAnnotationPresent(Inject.class)) {
                    //Получаю доступ к аннотации
                    Inject annotation = declaredField.getDeclaredAnnotation(Inject.class);
                    switch (annotation.arg()) {
                        case CONTEXT:
                            declaredField.set(obj, context);
                            break;
                        case ARGS:
                            declaredField.set(obj, arg);
                            break;

                    }
                }
            }
        }catch(Exception e){
            System.out.println("ERROR in TEST: " + e);
        }
    }

    @Test
    void run() {
        try {
            assertNotNull(obj);
            obj.run();
            assertEquals(4.0, context.popFromStack());
        }catch(Exception e){
            System.out.println("ERROR in TEST: " + e);
        }
    }
}