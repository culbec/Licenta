package encoder;

public class CircularEncoding extends Encoder {
    final int DEFAULT_CIRCULAR_ENCODING_LENGTH = 3;
    private final int length;

    public CircularEncoding(int length) {
        super();
        this.length = length > 2 ? length : DEFAULT_CIRCULAR_ENCODING_LENGTH;
    }

    @Override
    public String encode(String m) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < m.length(); i++) {
            result.append(m.charAt((i + this.length) % m.length()));
        }

        return result.toString();
    }
}
