import org.graalvm.polyglot.Context;
import org.graalvm.polyglot.Value;

public class ExtendJava {
    public static void main(String[] args) {
        String language = "js";
        try (Context context = Context.newBuilder().allowNativeAccess(true).build()) {
            for (String arg : args) {
                if (arg.startsWith("-")) {
                    language = arg.substring(1);
                } else {
                    Value v = context.eval(language, arg);
                    System.out.println(v);
                }
            }
        }
    }
}
