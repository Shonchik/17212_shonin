import java.io.FileInputStream;
import java.io.InputStream;
import java.lang.reflect.Field;
import java.lang.reflect.Proxy;
import java.util.List;
import java.util.Properties;
import java.util.TreeMap;

public class Factory {

    private static Properties property = null;
    private static TreeMap<String, Class> classes = null;

    private static Context context;

    static {
        try (InputStream reader = new FileInputStream("src\\commands.properties")) {
            classes = new TreeMap<String, Class>();

            property = new Properties();
            property.load(reader);

            context = new Context();

        } catch (Exception e) {
            System.out.println("ERROR FACTORY: " + e);
        }
    }

    public static CommandClass createCommand(List<String> cmd) throws Exception {
        Class<?> className = null;
        CommandClass commandObj = null;
        String key = property.getProperty(cmd.get(0).toUpperCase());

        if (null == key) {
            throw new Exception("Wrong command: " + cmd.get(0));
        }

        className = Class.forName(key);
        commandObj = (CommandClass) className.newInstance();

        Field[] declaredFields = className.getDeclaredFields();
        for (Field declaredField : declaredFields) {
            declaredField.setAccessible(true);
            if (declaredField.isAnnotationPresent(Inject.class)) {
                Inject annotation = declaredField.getDeclaredAnnotation(Inject.class);
                switch (annotation.arg()) {
                    case CONTEXT:
                        declaredField.set(commandObj, context);
                        break;
                    case ARGS:
                        declaredField.set(commandObj, cmd);
                        break;
                }
            }
        }

        CommandClass userProxy = (CommandClass) Proxy.newProxyInstance(
                commandObj.getClass().getClassLoader(),
                commandObj.getClass().getInterfaces(),
                new ProxyCommand(commandObj));

        commandObj = userProxy;


        return commandObj;
    }
}