[[
   #grammar cf

   #define start     ::= form;
   #define start     ::= $eof;

   #define form      ::= 
<=
      root ( public_namespace (
        singleton (
          nameattr ( identifier = program )
          script_function (
            code (
              expression (
                variable_identifier = current 
                assign = 0
                expression (
                  reference = forms'SDIDialog
                  message = new
                )
              )
=>
                          "<" "Form" property* form_closing_tag
<=
              returning (  
                expression (
                  identifier = current
                )
              )
            )
          )
        )
      ) )
=>;

   #define property       ::=
<=
        expression (
          expression (
            identifier = current

            message (
              identifier = $current
            )
            property_parameter = 0
          )
          assign = 0
          expression (
             new_reference = system'Variant
             message = 0
             expression (
=>
               $identifier "=" value
<=
             )
          )
        )
=>;

   #define member           ::=
<=
            code (
              expression (
                variable_identifier = current 
                assign = 0
                expression (
                  reference = forms'Label
                  message = new
                )
              )
=>
                            "<" "Label" property* label_closing_tag
<=
              expression (
                expression (
                  prev_identifier = current
                )
                message ( identifier = appendControl )
                expression (
                  identifier = current
                )  
              )
            )
=>;

   #define member           ::=
<=
            code (
              expression (
                variable_identifier = current 
                assign = 0
                expression (
                  reference = forms'Button
                  message = new
                )
              )
=>
                            "<" "Button" property* button_closing_tag
<=
              expression (
                expression (
                  prev_identifier = current
                )
                message ( identifier = appendControl )
                expression (
                  identifier = current
                )  
              )
            )
=>;

   #define form_closing_tag ::= 
                           ">" member* "<" "/" "Form" ">";

   #define label_closing_tag ::= 
                           ">" "<" "/" "Label" ">";

   #define button_closing_tag ::= 
                           ">" "<" "/" "Button" ">";

   #define value            ::= <= literal = "$literal" =>;

]]
        