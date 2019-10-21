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
        <title>NRE-Utility: /mnt/c/Users/abell/Documents/GitHub/NRE-Utility/src/Utility/UnorderedMap/NRE_UnorderedMap.hpp File Reference</title>
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
<li class="navelem"><a class="el" href="dir_68267d1309a1af8e8297ef4c3efbcdba.php">src</a></li><li class="navelem"><a class="el" href="dir_9761b53e3d9349800c0cb59b71c8cd3d.php">Utility</a></li><li class="navelem"><a class="el" href="dir_991de73145b56847179a6354dd08e51d.php">UnorderedMap</a></li>  </ul>
</div>
</div><!-- top -->
<div class="header">
  <div class="summary">
<a href="#nested-classes">Classes</a> &#124;
<a href="#namespaces">Namespaces</a> &#124;
<a href="#func-members">Functions</a>  </div>
  <div class="headertitle">
<div class="title">NRE_UnorderedMap.hpp File Reference</div>  </div>
</div><!--header-->
<div class="contents">

<p>Declaration of <a class="el" href="namespace_utility.php" title="Utility&#39;s API. ">Utility</a>'s API's Container : UnorderedMap.  
<a href="#details">More...</a></p>
<div class="textblock"><code>#include &quot;<a class="el" href="_n_r_e___hash_table_8hpp_source.php">../Detail/HashTable/NRE_HashTable.hpp</a>&quot;</code><br />
<code>#include &quot;NRE_UnorderedMap.tpp&quot;</code><br />
</div>
<p><a href="_n_r_e___unordered_map_8hpp_source.php">Go to the source code of this file.</a></p>
<table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="nested-classes"></a>
Classes</h2></td></tr>
<tr class="memitem:"><td class="memItemLeft" align="right" valign="top">class &#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="class_n_r_e_1_1_utility_1_1_unordered_map.php">NRE::Utility::UnorderedMap&lt; Key, T, StoreHash, Hash, KeyEqual &gt;</a></td></tr>
<tr class="memdesc:"><td class="mdescLeft">&#160;</td><td class="mdescRight">An unordered map, associative unordered container.  <a href="class_n_r_e_1_1_utility_1_1_unordered_map.php#details">More...</a><br /></td></tr>
<tr class="separator:"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="namespaces"></a>
Namespaces</h2></td></tr>
<tr class="memitem:namespace_n_r_e"><td class="memItemLeft" align="right" valign="top"> &#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="namespace_n_r_e.php">NRE</a></td></tr>
<tr class="memdesc:namespace_n_r_e"><td class="mdescLeft">&#160;</td><td class="mdescRight">The NearlyRealEngine's global namespace. <br /></td></tr>
<tr class="separator:"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:namespace_utility"><td class="memItemLeft" align="right" valign="top"> &#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="namespace_utility.php">Utility</a></td></tr>
<tr class="memdesc:namespace_utility"><td class="mdescLeft">&#160;</td><td class="mdescRight"><a class="el" href="namespace_utility.php" title="Utility&#39;s API. ">Utility</a>'s API. <br /></td></tr>
<tr class="separator:"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="func-members"></a>
Functions</h2></td></tr>
<tr class="memitem:a500aca05a218e02dc9bfdd9a77bba5c0"><td class="memTemplParams" colspan="2">template&lt;class Key , class T , bool StoreHash, class Hash , class KeyEqual &gt; </td></tr>
<tr class="memitem:a500aca05a218e02dc9bfdd9a77bba5c0"><td class="memTemplItemLeft" align="right" valign="top">std::ostream &amp;&#160;</td><td class="memTemplItemRight" valign="bottom"><a class="el" href="_n_r_e___unordered_map_8hpp.php#a500aca05a218e02dc9bfdd9a77bba5c0">NRE::Utility::operator&lt;&lt;</a> (std::ostream &amp;stream, UnorderedMap&lt; Key, T, StoreHash, Hash, KeyEqual &gt; const &amp;o)</td></tr>
<tr class="separator:a500aca05a218e02dc9bfdd9a77bba5c0"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table>
<a name="details" id="details"></a><h2 class="groupheader">Detailed Description</h2>
<div class="textblock"><p>Declaration of <a class="el" href="namespace_utility.php" title="Utility&#39;s API. ">Utility</a>'s API's Container : UnorderedMap. </p>
<dl class="section author"><dt>Author</dt><dd>Louis ABEL </dd></dl>
<dl class="section date"><dt>Date</dt><dd>01/07/2019 </dd></dl>
<dl class="section copyright"><dt>Copyright</dt><dd>CC-BY-NC-SA </dd></dl>
</div><h2 class="groupheader">Function Documentation</h2>
<a class="anchor" id="file_a500aca05a218e02dc9bfdd9a77bba5c0"></a>
<div class="memitem">
<div class="memproto">
<div class="memtemplate">
template&lt;class Key , class T , bool StoreHash, class Hash , class KeyEqual &gt; </div>
      <table class="memname">
        <tr>
          <td class="memname">std::ostream&amp; NRE::Utility::operator&lt;&lt; </td>
          <td>(</td>
          <td class="paramtype">std::ostream &amp;&#160;</td>
          <td class="paramname"><em>stream</em>, </td>
        </tr>
        <tr>
          <td class="paramkey"></td>
          <td></td>
          <td class="paramtype"><a class="el" href="class_n_r_e_1_1_utility_1_1_unordered_map.php">UnorderedMap</a>&lt; Key, T, StoreHash, Hash, KeyEqual &gt; const &amp;&#160;</td>
          <td class="paramname"><em>o</em>&#160;</td>
        </tr>
        <tr>
          <td></td>
          <td>)</td>
          <td></td><td></td>
        </tr>
      </table>
</div><div class="memdoc">
<p>Output stream operator for the object </p><dl class="params"><dt>Parameters</dt><dd>
  <table class="params">
    <tr><td class="paramname">stream</td><td>the stream to add the object's string representation </td></tr>
    <tr><td class="paramname">o</td><td>the object to add in the stream </td></tr>
  </table>
  </dd>
</dl>
<dl class="section return"><dt>Returns</dt><dd>the modified stream </dd></dl>

</div>
</div>
</div><!-- contents -->
<!-- HTML footer for doxygen 1.8.8-->
<!-- start footer part -->
</div>
</div>
</div>
</div>
</body>
</html>
