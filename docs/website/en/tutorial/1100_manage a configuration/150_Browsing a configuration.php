<div class="prototype">
  Browsing a configuration
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    Browsing a configuration is often required to fully handle it.
    If some program may only need a few fixed field with set values,
    most of them need to read all field a node can have. With what
    you have learnt in the previous part, you can alreayd browse a
    few nodes: those who are arrays, with bunny_configuration_access,
    but not hashmap!<br />
    <br />
    In this part, you will learn how to browse hashmap too and how
    to retrieve informations from nodes.
  </p>
  <br />
  <br />

  <div class="prototype">
    $Tt_bunny_configuration@ *$Sbunny_configuration_first@($Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns the first child of the node you sent. Children are
    sorted by name. This function may return bunny_configuration_end(configuration)
    if the sent node was empty.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tt_bunny_configuration@ *$Sbunny_configuration_next@($Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns the next brother (or sister) of the node you sent.
    Children are sorted by name. This function may bunny_configuration_end(configuration) if the sent node was the last one.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tt_bunny_configuration@ *$Sbunny_configuration_end@($Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns a the sent node children terminator.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tbool@ $Sbunny_configuration_is_last@($Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns $Ctrue@ if the sent node is the last children of its
    parent.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tt_bunny_configuration@ *$Sbunny_configuration_get_parent@($Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns the parent of the sent node. $CNULL@ if the sent node
    is the root node.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tt_bunny_configuration@ *$Sbunny_configuration_get_root@($Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns the root of the sent node: the only node without parent
    in its genealogy.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Kconst@ $Tchar@ *$Sbunny_configuration_get_name@($Kconst@ $Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns the name of the sent node. Every node have a name,
    even nodes that are in an array, they are simply the name of their parent
    followed by brackets containing their address.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Kconst@ $Tchar@ *$Sbunny_configuration_get_address@($Kconst@ $Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns the address of the sent node. It is made of all names
    from all nodes from the one you sent to the root. If there is some arrays between
    them, the address is designed intelligently: you will not find
    Array.Array[1].Node kind of stuff, but Array[1].node, of course.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tsize_t@ $Sbunny_configuration_get_nbr_child@($Kconst@ $Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns how many named children the node have: the size
    of its hashmap.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tsize_t@ $Sbunny_configuration_get_nbr_case@($Kconst@ $Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function returns how many indexed children the node have: the size
    of its array.
  </p>
  <br />

  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    The first step of this program is the filling of the configuration by hand.
    It starts with the node creation followed by the call to
    bunny_configuration_create_mode with $Ctrue@ as parameter. After that,
    the configuration is filled and then the create mode is disabled so
    access to the configuration does not create new nodes.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/152_conf_filling.c"); ?>
    </div>
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    In this following part, the $L"Country"@ node hashmap is browsed.
    The bunny_configuration_first, end and next functions make the for loop.<br />
    <br />
    The first line inside the loop try to retrieve from the children a string.
    If it fails, the program stops.<br />
    <br />
    The second line print the name of the children and its retrieved value.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/153_loop_browsing.c"); ?>
    </div>
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    This time, the $L"Country.Region[0].Department"@ is browsed. This field
    does not contain a hashmap like before but have some elements inside its
    array: Seine-et-Marne, Val-de-Marne and Paris.<br />
    <br />
    As we treat an array, this time we use an int. By requested the node at
    the sent index, we can retrieve an existing node or $CNULL@ if there is
    none at the sent index. If the create mode was enabled with this fashion,
    we could have created new nodes!<br />
    An alternative, without disabling the create mode would be to use
    bunny_configuration_get_nbr_case as termination condition.<br />
    <br />
    In the loop, we try to retrieve a string from the extracted node.<br />
    <br />
    After that, we print its name and its value.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/154_loop_array.c"); ?>
    </div>
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    Here, we check the Country.Region[0].Department array is 3 node long. It
    is supposed to be, as it contains "Seine-et-Marne", "Val-de-Marne" and
    "Paris".<br />
    <br />
    Right after, the access to the Country node to check there is 4 child:
    Name, Population, Regime and Region. We also check the parent node of
    Country is the root node.<br />
    <br />
    The final part check Coutry.Region address and Country.Region[1].Department
    are correct.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/155_various_data.c"); ?>
    </div>
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    The whole program.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/151_browsing_configuration.c"); ?>
    </div>
  </p>

</div>
