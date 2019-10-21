<!-- HTML header for doxygen 1.8.8-->
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <!-- For Mobile Devices -->
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta http-equiv="Content-Type" content="text/xhtml;charset=UTF-8"/>
        <meta name="generator" content="Doxygen 1.8.11"/>
        <script type="text/javascript" src="../../js/jquery-2.1.1.min.js"></script>
        <title>NRE-Utility: /mnt/c/Users/abell/Documents/GitHub/NRE-Utility/src/Utility/Interfaces/Stringable/NRE_Stringable.hpp Source File</title>
        <!--<link href="tabs.css" rel="stylesheet" type="text/css"/>-->
        <script type="text/javascript" src="dynsections.js"></script>
        <link href="search/search.css" rel="stylesheet" type="text/css"/>
<script type="text/javascript" src="search/searchdata.js"></script>
<script type="text/javascript" src="search/search.js"></script>
<script type="text/javascript">
  $(document).ready(function() { init_search(); });
</script>
        <link href="doxygen.css" rel="stylesheet" type="text/css" />
        <link href="style.css" rel="stylesheet" type="text/css"/>
        <link href='https://fonts.googleapis.com/css?family=Roboto+Slab' rel='stylesheet' type='text/css'>
        <?php
            include '../../php/navigation.php';
            if (!isset($_COOKIE["theme"]) || $_COOKIE["theme"] == "dark") {
                echo '<link href="../../css/dark/bootstrap.css" rel="stylesheet">';
            } else {
                echo '<link href="../../css/light/bootstrap.css" rel="stylesheet">';
            }
        ?>
        <script src="../../js/bootstrap.min.js"></script>
        <script type="text/javascript" src="doxy-boot.js"></script>
    </head>
    <body>
        <div class="container-fluid">
            <header class="page-header">
                <a href="../../../index.php">
                    <img src="../../img/Logo.png" class="logo img-responsive"/>
                </a>
            </header>
            <?php addNavigationBarInl(false); ?>
            <div id="top" class="row"><!-- do not remove this div, it is closed by doxygen! -->
                <div class="col-lg-12">
                    <div class="panel panel-default">
                        <div class="panel-body">
<!-- end header part -->
<!-- Generated by Doxygen 1.8.11 -->
<script type="text/javascript">
var searchBox = new SearchBox("searchBox", "search",false,'Search');
</script>
  <div id="navrow1" class="tabs">
    <ul class="tablist">
      <li><a href="index.php"><span>Main&#160;Page</span></a></li>
      <li><a href="namespaces.php"><span>Namespaces</span></a></li>
      <li><a href="annotated.php"><span>Classes</span></a></li>
      <li class="current"><a href="files.php"><span>Files</span></a></li>
      <li>
        <div id="MSearchBox" class="MSearchBoxInactive">
        <span class="left">
          <img id="MSearchSelect" src="search/mag_sel.png"
               onmouseover="return searchBox.OnSearchSelectShow()"
               onmouseout="return searchBox.OnSearchSelectHide()"
               alt=""/>
          <input type="text" id="MSearchField" value="Search" accesskey="S"
               onfocus="searchBox.OnSearchFieldFocus(true)" 
               onblur="searchBox.OnSearchFieldFocus(false)" 
               onkeyup="searchBox.OnSearchFieldChange(event)"/>
          </span><span class="right">
            <a id="MSearchClose" href="javascript:searchBox.CloseResultsWindow()"><img id="MSearchCloseImg" border="0" src="search/close.png" alt=""/></a>
          </span>
        </div>
      </li>
    </ul>
  </div>
  <div id="navrow2" class="tabs2">
    <ul class="tablist">
      <li><a href="files.php"><span>File&#160;List</span></a></li>
    </ul>
  </div>
<!-- window showing the filter options -->
<div id="MSearchSelectWindow"
     onmouseover="return searchBox.OnSearchSelectShow()"
     onmouseout="return searchBox.OnSearchSelectHide()"
     onkeydown="return searchBox.OnSearchSelectKey(event)">
</div>

<!-- iframe showing the search results (closed by default) -->
<div id="MSearchResultsWindow">
<iframe src="javascript:void(0)" frameborder="0" 
        name="MSearchResults" id="MSearchResults">
</iframe>
</div>

<div id="nav-path" class="navpath">
  <ul>
<li class="navelem"><a class="el" href="dir_68267d1309a1af8e8297ef4c3efbcdba.php">src</a></li><li class="navelem"><a class="el" href="dir_9761b53e3d9349800c0cb59b71c8cd3d.php">Utility</a></li><li class="navelem"><a class="el" href="dir_b7017f46de0d068332e4c2d3bf7ed59e.php">Interfaces</a></li><li class="navelem"><a class="el" href="dir_e5fa4c25397d459b4bc4865406c131ec.php">Stringable</a></li>  </ul>
</div>
</div><!-- top -->
<div class="header">
  <div class="headertitle">
<div class="title">NRE_Stringable.hpp</div>  </div>
</div><!--header-->
<div class="contents">
<a href="_n_r_e___stringable_8hpp.php">Go to the documentation of this file.</a><div class="fragment"><div class="line"><a name="l00001"></a><span class="lineno">    1</span>&#160;</div><div class="line"><a name="l00010"></a><span class="lineno">   10</span>&#160;<span class="preprocessor">     #pragma once</span></div><div class="line"><a name="l00011"></a><span class="lineno">   11</span>&#160;</div><div class="line"><a name="l00012"></a><span class="lineno">   12</span>&#160;<span class="preprocessor">     #include &lt;cassert&gt;</span></div><div class="line"><a name="l00013"></a><span class="lineno">   13</span>&#160;</div><div class="line"><a name="l00014"></a><span class="lineno">   14</span>&#160;<span class="preprocessor">    #include &quot;../NRE_StaticInterface.hpp&quot;</span></div><div class="line"><a name="l00015"></a><span class="lineno">   15</span>&#160;<span class="preprocessor">    #include &quot;../../String/NRE_String.hpp&quot;</span></div><div class="line"><a name="l00016"></a><span class="lineno">   16</span>&#160;</div><div class="line"><a name="l00021"></a><span class="lineno">   21</span>&#160;    <span class="keyword">namespace </span><a class="code" href="namespace_n_r_e.php">NRE</a> {</div><div class="line"><a name="l00026"></a><span class="lineno">   26</span>&#160;        <span class="keyword">namespace </span><a class="code" href="namespace_utility.php">Utility</a> {</div><div class="line"><a name="l00027"></a><span class="lineno">   27</span>&#160;</div><div class="line"><a name="l00032"></a><span class="lineno">   32</span>&#160;            <span class="keyword">template</span> &lt;<span class="keyword">class</span> T&gt;</div><div class="line"><a name="l00033"></a><span class="lineno"><a class="line" href="class_n_r_e_1_1_utility_1_1_stringable.php">   33</a></span>&#160;            <span class="keyword">class </span><a class="code" href="class_n_r_e_1_1_utility_1_1_stringable.php">Stringable</a> : <span class="keyword">public</span> <a class="code" href="class_n_r_e_1_1_utility_1_1_static_interface.php">StaticInterface</a>&lt;T, Stringable&gt; {</div><div class="line"><a name="l00034"></a><span class="lineno">   34</span>&#160;                <span class="keyword">public</span>:    <span class="comment">// Methods</span></div><div class="line"><a name="l00039"></a><span class="lineno"><a class="line" href="class_n_r_e_1_1_utility_1_1_stringable.php#a858907f8126e9c210854ddb659dd17ee">   39</a></span>&#160;<span class="comment"></span>                    <a class="code" href="class_n_r_e_1_1_utility_1_1_basic_string.php">String</a> <a class="code" href="class_n_r_e_1_1_utility_1_1_stringable.php#a858907f8126e9c210854ddb659dd17ee">toString</a>()<span class="keyword"> const </span>{</div><div class="line"><a name="l00040"></a><span class="lineno">   40</span>&#160;                        <span class="keywordflow">return</span> this-&gt;<a class="code" href="class_n_r_e_1_1_utility_1_1_static_interface.php#a72fd5f7816f2a8309328186e1bf2b2f5">impl</a>().toString();</div><div class="line"><a name="l00041"></a><span class="lineno">   41</span>&#160;                    }</div><div class="line"><a name="l00048"></a><span class="lineno"><a class="line" href="class_n_r_e_1_1_utility_1_1_stringable.php#a2f1f99296816e02780f1f74ebba13f22">   48</a></span>&#160;                    <span class="keyword">friend</span> std::ostream&amp; <a class="code" href="class_n_r_e_1_1_utility_1_1_stringable.php#a2f1f99296816e02780f1f74ebba13f22">operator &lt;&lt;</a>(std::ostream&amp; stream, T <span class="keyword">const</span>&amp; o) {</div><div class="line"><a name="l00049"></a><span class="lineno">   49</span>&#160;                        <span class="keywordflow">return</span> stream &lt;&lt; o.Stringable&lt;T&gt;::toString();</div><div class="line"><a name="l00050"></a><span class="lineno">   50</span>&#160;                    }</div><div class="line"><a name="l00051"></a><span class="lineno">   51</span>&#160;            };</div><div class="line"><a name="l00052"></a><span class="lineno">   52</span>&#160;        }</div><div class="line"><a name="l00053"></a><span class="lineno">   53</span>&#160;    }</div><div class="ttc" id="class_n_r_e_1_1_utility_1_1_static_interface_php_a72fd5f7816f2a8309328186e1bf2b2f5"><div class="ttname"><a href="class_n_r_e_1_1_utility_1_1_static_interface.php#a72fd5f7816f2a8309328186e1bf2b2f5">NRE::Utility::StaticInterface&lt; T, Stringable &gt;::impl</a></div><div class="ttdeci">T &amp; impl()</div><div class="ttdef"><b>Definition:</b> NRE_StaticInterface.hpp:33</div></div>
<div class="ttc" id="class_n_r_e_1_1_utility_1_1_stringable_php"><div class="ttname"><a href="class_n_r_e_1_1_utility_1_1_stringable.php">NRE::Utility::Stringable</a></div><div class="ttdoc">Describe an stringable object. </div><div class="ttdef"><b>Definition:</b> NRE_Stringable.hpp:33</div></div>
<div class="ttc" id="class_n_r_e_1_1_utility_1_1_stringable_php_a858907f8126e9c210854ddb659dd17ee"><div class="ttname"><a href="class_n_r_e_1_1_utility_1_1_stringable.php#a858907f8126e9c210854ddb659dd17ee">NRE::Utility::Stringable::toString</a></div><div class="ttdeci">String toString() const </div><div class="ttdef"><b>Definition:</b> NRE_Stringable.hpp:39</div></div>
<div class="ttc" id="namespace_n_r_e_php"><div class="ttname"><a href="namespace_n_r_e.php">NRE</a></div><div class="ttdoc">The NearlyRealEngine&amp;#39;s global namespace. </div></div>
<div class="ttc" id="class_n_r_e_1_1_utility_1_1_basic_string_php"><div class="ttname"><a href="class_n_r_e_1_1_utility_1_1_basic_string.php">NRE::Utility::BasicString</a></div><div class="ttdoc">A basic template string, with dynamic size, guarantee to be in contiguous memory. ...</div><div class="ttdef"><b>Definition:</b> NRE_String.hpp:38</div></div>
<div class="ttc" id="class_n_r_e_1_1_utility_1_1_static_interface_php"><div class="ttname"><a href="class_n_r_e_1_1_utility_1_1_static_interface.php">NRE::Utility::StaticInterface</a></div><div class="ttdoc">Describe an object using CRTP to create static interface (static polymorphism) </div><div class="ttdef"><b>Definition:</b> NRE_StaticInterface.hpp:28</div></div>
<div class="ttc" id="namespace_utility_php"><div class="ttname"><a href="namespace_utility.php">Utility</a></div><div class="ttdoc">Utility&amp;#39;s API. </div></div>
<div class="ttc" id="class_n_r_e_1_1_utility_1_1_stringable_php_a2f1f99296816e02780f1f74ebba13f22"><div class="ttname"><a href="class_n_r_e_1_1_utility_1_1_stringable.php#a2f1f99296816e02780f1f74ebba13f22">NRE::Utility::Stringable::operator&lt;&lt;</a></div><div class="ttdeci">friend std::ostream &amp; operator&lt;&lt;(std::ostream &amp;stream, T const &amp;o)</div><div class="ttdef"><b>Definition:</b> NRE_Stringable.hpp:48</div></div>
</div><!-- fragment --></div><!-- contents -->
<!-- HTML footer for doxygen 1.8.8-->
<!-- start footer part -->
</div>
</div>
</div>
</div>
</body>
</html>
