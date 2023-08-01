package com.example.fasmdllmanaged;

import java.lang.annotation.*;

@Documented
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.TYPE)
@interface AssemblyInfo {
    String title() default "";
    String description() default "";
    String configuration() default "";
    String company() default "";
    String product() default "";
    String copyright() default "";
    String trademark() default "";
    String culture() default "";
    String version() default "1.0.*";
}

@AssemblyInfo(
    title = "fasmdll_managed",
    product = "fasmdll_managed",
    copyright = "Copyright (c)  2012"
)
public class FasmDllManaged {
    public static void main(String[] args) {
        AssemblyInfo info = FasmDllManaged.class.getAnnotation(AssemblyInfo.class);
        System.out.println("Assembly title: " + info.title());
        System.out.println("Product: " + info.product());
        System.out.println("Copyright: " + info.copyright());
    }
}
