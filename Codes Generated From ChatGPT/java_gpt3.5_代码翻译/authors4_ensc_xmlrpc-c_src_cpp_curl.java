import java.util.HashMap;
import java.util.Map;

public class CurlXMLTransport {

    private final Map<String, Object> options;

    public CurlXMLTransport() {
        options = new HashMap<>();
        setupGlobalConstant();
    }

    public void setOption(String optionName, Object optionValue) {
        options.put(optionName, optionValue);
    }

    public Object getOption(String optionName) {
        return options.get(optionName);
    }

    public void clearOptions() {
        options.clear();
    }

    private void setupGlobalConstant() {
        // 在此处执行全局初始化
    }

    private void teardownGlobalConstant() {
        // 在此处执行全局销毁
    }

    // 在这里添加其他方法以实现XML-RPC与Curl相关的功能，例如发送请求、处理响应等

    @Override
    protected void finalize() {
        teardownGlobalConstant();
    }

    public static class Builder {
        private final CurlXMLTransport transport;

        public Builder() {
            transport = new CurlXMLTransport();
        }

        public Builder setNetworkInterface(String networkInterface) {
            transport.setOption("network_interface", networkInterface);
            return this;
        }

        public Builder setNoSslVerifyPeer(boolean noSslVerifyPeer) {
            transport.setOption("no_ssl_verify_peer", noSslVerifyPeer);
            return this;
        }

        public Builder setNoSslVerifyHost(boolean noSslVerifyHost) {
            transport.setOption("no_ssl_verify_host", noSslVerifyHost);
            return this;
        }

        public Builder setUserAgent(String userAgent) {
            transport.setOption("user_agent", userAgent);
            return this;
        }

        // 在这里添加其他方法，以设置和获取其他选项，如SSL证书、代理、超时等。

        public CurlXMLTransport build() {
            return transport;
        }
    }

    public static void main(String[] args) {
        // 使用Builder设置选项并创建CurlXMLTransport对象
        CurlXMLTransport transport = new CurlXMLTransport.Builder()
                .setNetworkInterface("eth0")
                .setNoSslVerifyPeer(true)
                .setNoSslVerifyHost(true)
                .setUserAgent("MyApp/1.0")
                .build();

        // 在这里使用CurlXMLTransport对象执行XML-RPC请求和处理响应。
    }
}