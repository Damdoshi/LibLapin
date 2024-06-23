<div class="prototype">
  Managing a configuration
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    Before being something modelized inside files, the configuration
    module is an in-memory data manager.<br />
    In this first part, we will learn how to create, delete and
    edit a configuration without talking about its storage.<br />
    <br />
    We will use <b>C11</b> features throught some functions, so
    your compiler should be ready for it: recent and set to plain
    C instead of C++. If you are using C++, alternatives to
    listed functions will be provided.
  </p>
  <br />
  <br />

  <div class="prototype">
    $Tt_bunny_configuration@ *$Sbunny_new_configuration@($Tvoid@);
  </div>
  <p>
    This function build a configuration node. It is the very start of
    a configuration when it does not came from a file. This configuration
    node must be freed with bunny_delete_configuration when you are done.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tvoid@ $Sbunny_delete_configuration@($Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    Delete a configuration node.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tvoid@ $Sbunny_configuration_create_mode@($Tbool@ $Screate_mode@);
  </div>
  <p>
    The create mode is a mode where some access provoke the creation of
    configuration node. It is mandatory to write a configuration from
    a virgin one. It is not mandatory to only write inside existing nodes.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Kconst@ $Tchar@ *$Sbunny_configuration_access($Kconst@ $Tt_bunny_configuration@ *$Sconfiguration@, $Sid@);
  </div>
  <p>
    This function return the node, children of $Sconfiguration@ and characterized
    by $Sid@. $Sid@ can be a string containing an address or an integer containing
    an index. Addresses in configuration work almost like structure access in C:
    <br /><br />
    <ul>
      <li>
        The '.' operator allows you to access a field and look for a named children,
        for example:<br />
        buffer.width<br />
        Access the width field which is inside buffer.
      </li>
      <li>
        The '->' operator allows you to access the address stored inside a field
        to access a named children, for example:<br />
        clipable->buffer<br />
        Assuming clipable contains the address of a field which have a child named buffer.
      </li>
      <li>
        The '[' ']' operator allows you to access a field and look for an indexed
        children, for example:<br />
        array[21]<br />
        Access the field n=21 in array.<br />
        <br />
        The value between brackets can use variable, which can be defined by
        address, like in C, for example:<br />
        people[account.id]<br />
        Will access in people the field at the index stored inside account.id.
      </li>
      <li>
        It is <b>currently unsupported</b>, but it will be in the future, the
        operator '[' ']' operator will allow you to access a field and look for
        a children value if the value between bracket is a string.
      </li>
    </ul>
    <br />
    <br />
    This functionnality needs C11.<br />
    Alternative functions are bunny_configuration_go_get_node and
    bunny_configuration_get_case.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tvoid@ $Sbunny_configuration_set($Tt_bunny_configuration@ *$Sconfiguration@, $Sdata@);
  </div>
  <p>
    This function set a value into the sent configuration. This value can be a
    string, an int or a double.<br />
    <br />
    This functionnality needs C11. <br />
    Alternative functions are bunny_configuration_set_string,
    bunny_configuration_set_double and bunny_configuration_set_int.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tbool@ $Sbunny_configuration_get($Tt_bunny_configuration@ *$Sconfiguration@, $Sdata@);
  </div>
  <p>
    This function get a value from the sent configuration. This value can be a
    $Tchar@**, an $Tint@* or a $Tdouble@*.<br />
    If value inside the node is not of the correct type but could be converted,
    it will. If the value was retrieved, the function returns $Ctrue@.<br />
    <br />
    This functionnality needs C11. <br />
    Alternative functions are bunny_configuration_get_string,
    bunny_configuration_get_double and bunny_configuration_get_int.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tvoid@ $Sbunny_configuration_go_set($Tt_bunny_configuration@ *$Sconfiguration@, $Sdata@, $Kconst@ $Tchar@ *$Saddress@);
  </div>
  <p>
    This function set a value into the sent configuration at the sent address.
    This value can be a string, an int or a double.<br />
    <br />
    This functionnality needs C11. <br />
    Alternative functions are bunny_configuration_go_set_string,
    bunny_configuration_go_set_double and bunny_configuration_go_set_int.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tbool@ $Sbunny_configuration_get($Tt_bunny_configuration@ *$Sconfiguration@, $Sdata@, $Kconst@ $Tchar@ *$Saddress@);
  </div>
  <p>
    This function get a value from the sent configuration at the sent address.
    This value can be a $Tchar@**, an $Tint@* or a $Tdouble@*.<br />
    If value inside the node is not of the correct type but could be converted,
    it will. If the value was retrieved, the function returns $Ctrue@.<br />
    <br />
    This functionnality needs C11. <br />
    Alternative functions are bunny_configuration_go_get_string,
    bunny_configuration_go_get_double and bunny_configuration_go_get_int.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    The below program show several operations made on a configuration with
    the most useful functions of the configuration module.<br />
    <br />
    It starts by creating a first configuration node with bunny_new_configuration.
    This creates a single and empty, for both named children and indexed children,
    but also as value, node: no children, no value.<br />
    <br />
    Following this operation, a little demo of what is the create mode. It is
    currently disabled, as it is by default: when calling the
    bunny_configuration_access function which is designed to get a node by
    its address, because this mode is disabled, the function cannot get it because
    it does not exist yet and it returns $CNULL@.<br />
    <br />
    Right after, we call bunny_configuration_create_mode with $Ctrue@ as parameter
    to enable it and retry with bunny_configuration_access. This time, the node
    is created.<br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/102_create_node.c"); ?>
    </div>
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    Now we have a Team.Player node and a pointer on it inside adr, we will
    store a value inside it. With bunny_configuration_set, we can set
    a value inside a node by its pointer.<br />
    <br />
    Right after, we try to fetch it and store it inside an integer variable
    and check its value. It matches the one we set before.<br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/103_set_get_value.c"); ?>
    </div>
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    Sometimes, it is more convenient to set a value from far away, without
    having to get its node before and then call a set function. Same thing
    goes for get functions.<br />
    For this purpose, the bunny_configuration_go_* family allow to set and
    get values from a parent node with relative address.<br />
    <br />
    In this part of the program, we set the Team.Player field from the root
    node we create at the very beginning to an integer value.<br />
    <br />
    From the root node again, we fetch it and check it is the same we set before.<br />
    <br />
    Finally, to prove that we set effectively the node that was pointed
    by adr before, we will fetch the value from it with the function we
    previously used, bunny_configuration_get and check it matches 68000.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/104_go_set_get_value.c"); ?>
    </div>
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    Do not forget to delete the configuration if you do not need it anymore.
    Note that it delete every data that was inside. If integers and doubles
    are not big deal, you should pay attention to strings you retrieved, their
    pointers will not be valid anymore!<br />
    Also pay attention to pointers to node that were below the node you
    delete: they will not be valid either after that.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/105_delete.c"); ?>
    </div>
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    The whole program, setting values with different fashion and fetching
    them right after.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/101_create_set_get_delete.c"); ?>
    </div>
  </p>

</div>
