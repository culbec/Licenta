package encoder;

public class NaiveEncoding extends Encoder {
    @Override
    public String encode(String m) {
        StringBuilder result = new StringBuilder();

        for (int i = m.length() - 1; i >= 0; i--) {
            result.append(m.charAt(i));
        }

        return result.toString();
    }
}
