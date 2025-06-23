package communication;

import encoder.Encoder;
import encoder.NaiveEncoding;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Communication {
    private final Encoder code;
    private final List<String> encodedMessages;

    public Communication(Encoder e) {
        // NaiveEncoding as default
        this.code = Objects.isNull(e) ? new NaiveEncoding() : e;
        this.encodedMessages = new ArrayList<>();
    }

    public void addMessage(String m) {
        this.encodedMessages.add(code.encode(m));
    }

    public List<String> getEncodedMessages() {
        return this.encodedMessages;
    }

    public String toString() {
        StringBuilder result = new StringBuilder();

        for (int i = 0; i < this.encodedMessages.size(); i++) {
            result.append(this.encodedMessages.get(i));
            if (i != this.encodedMessages.size() - 1) {
                result.append('#');
            }
        }

        return result.toString();
    }
}
