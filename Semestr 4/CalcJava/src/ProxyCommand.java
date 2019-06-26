import java.lang.reflect.Field;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.util.List;
import java.util.logging.Logger;

public class ProxyCommand implements InvocationHandler {
    private Object obj;
    private static final Logger log = (Logger) Logger.getLogger(String.valueOf(Calculator.class));

    public ProxyCommand(Object f1) {
        obj = f1;
    }

    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {

        Class<?> className = Class.forName(obj.getClass().getName());

        Context c = null;
        List<String> list = null;

        Field[] declaredFields = className.getDeclaredFields();
        for (Field declaredField : declaredFields) {
            declaredField.setAccessible(true);
            if (declaredField.isAnnotationPresent(Inject.class)) {
                Inject annotation = declaredField.getDeclaredAnnotation(Inject.class);
                switch (annotation.arg()) {
                    case CONTEXT:
                        c = (Context) declaredField.get(obj);
                        break;
                    case ARGS:
                        list = (List<String>) declaredField.get(obj);
                        break;
                }
            }
        }


        Object result = method.invoke(obj, args);

        return result;
    }
}