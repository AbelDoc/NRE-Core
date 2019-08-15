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
        <title>NRE-Utility: NRE::Utility::BucketEntryHash&lt; StoreHash &gt; Class Template Reference</title>
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
      <li class="current"><a href="annotated.php"><span>Classes</span></a></li>
      <li><a href="files.php"><span>Files</span></a></li>
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
      <li><a href="annotated.php"><span>Class&#160;List</span></a></li>
      <li><a href="classes.php"><span>Class&#160;Index</span></a></li>
      <li><a href="hierarchy.php"><span>Class&#160;Hierarchy</span></a></li>
      <li><a href="functions.php"><span>Class&#160;Members</span></a></li>
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
<li class="navelem"><a class="el" href="namespace_n_r_e.php">NRE</a></li><li class="navelem"><b>Utility</b></li><li class="navelem"><a class="el" href="class_n_r_e_1_1_utility_1_1_bucket_entry_hash.php">BucketEntryHash</a></li>  </ul>
</div>
</div><!-- top -->
<div class="header">
  <div class="summary">
<a href="#pub-methods">Public Member Functions</a> &#124;
<a href="#pro-methods">Protected Member Functions</a> &#124;
<a href="class_n_r_e_1_1_utility_1_1_bucket_entry_hash-members.php">List of all members</a>  </div>
  <div class="headertitle">
<div class="title">NRE::Utility::BucketEntryHash&lt; StoreHash &gt; Class Template Reference</div>  </div>
</div><!--header-->
<div class="contents">

<p>Used to store the key hash, or not depending on the template value.  
 <a href="class_n_r_e_1_1_utility_1_1_bucket_entry_hash.php#details">More...</a></p>

<p><code>#include &lt;<a class="el" href="_n_r_e___hash_table_8hpp_source.php">NRE_HashTable.hpp</a>&gt;</code></p>
<div class="dynheader">
Inheritance diagram for NRE::Utility::BucketEntryHash&lt; StoreHash &gt;:</div>
<div class="dyncontent">
 <div class="center">
  <img src="class_n_r_e_1_1_utility_1_1_bucket_entry_hash.png" usemap="#NRE::Utility::BucketEntryHash_3C_20StoreHash_20_3E_map" alt=""/>
  <map id="NRE::Utility::BucketEntryHash_3C_20StoreHash_20_3E_map" name="NRE::Utility::BucketEntryHash&lt; StoreHash &gt;_map">
<area href="class_n_r_e_1_1_utility_1_1_bucket_entry.php" alt="NRE::Utility::BucketEntry&lt; NRE::Utility::Pair, STORE_HASH &gt;" shape="rect" coords="0,56,353,80"/>
<area href="class_n_r_e_1_1_utility_1_1_bucket_entry.php" title="A bucket entry used as the hash table elements. " alt="NRE::Utility::BucketEntry&lt; ValueType, StoreHash &gt;" shape="rect" coords="363,56,716,80"/>
</map>
 </div></div>
<table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="pub-methods"></a>
Public Member Functions</h2></td></tr>
<tr class="memitem:a6a0f44c490c0f828d1377a231d1166d4"><td class="memItemLeft" align="right" valign="top">bool&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="class_n_r_e_1_1_utility_1_1_bucket_entry_hash.php#a6a0f44c490c0f828d1377a231d1166d4">bucketHashEquals</a> (std::size_t) const </td></tr>
<tr class="separator:a6a0f44c490c0f828d1377a231d1166d4"><td class="memSeparator" colspan="2">&#160;</td></tr>
<tr class="memitem:a649b8be8873d8550244a7656a98921e1"><td class="memItemLeft" align="right" valign="top">TruncatedHash&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="class_n_r_e_1_1_utility_1_1_bucket_entry_hash.php#a649b8be8873d8550244a7656a98921e1">getTruncatedHash</a> () const </td></tr>
<tr class="separator:a649b8be8873d8550244a7656a98921e1"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table><table class="memberdecls">
<tr class="heading"><td colspan="2"><h2 class="groupheader"><a name="pro-methods"></a>
Protected Member Functions</h2></td></tr>
<tr class="memitem:ac5fb7ad7eaffbd1b53fb77c49a8e2722"><td class="memItemLeft" align="right" valign="top">void&#160;</td><td class="memItemRight" valign="bottom"><a class="el" href="class_n_r_e_1_1_utility_1_1_bucket_entry_hash.php#ac5fb7ad7eaffbd1b53fb77c49a8e2722">setHash</a> (TruncatedHash)</td></tr>
<tr class="separator:ac5fb7ad7eaffbd1b53fb77c49a8e2722"><td class="memSeparator" colspan="2">&#160;</td></tr>
</table>
<a name="details" id="details"></a><h2 class="groupheader">Detailed Description</h2>
<div class="textblock"><h3>template&lt;bool StoreHash&gt;<br />
class NRE::Utility::BucketEntryHash&lt; StoreHash &gt;</h3>

<p>Used to store the key hash, or not depending on the template value. </p>
</div><h2 class="groupheader">Member Function Documentation</h2>
<a class="anchor" id="a6a0f44c490c0f828d1377a231d1166d4"></a>
<div class="memitem">
<div class="memproto">
<div class="memtemplate">
template&lt;bool StoreHash&gt; </div>
<table class="mlabels">
  <tr>
  <td class="mlabels-left">
      <table class="memname">
        <tr>
          <td class="memname">bool <a class="el" href="class_n_r_e_1_1_utility_1_1_bucket_entry_hash.php">NRE::Utility::BucketEntryHash</a>&lt; StoreHash &gt;::bucketHashEquals </td>
          <td>(</td>
          <td class="paramtype">std::size_t&#160;</td>
          <td class="paramname"></td><td>)</td>
          <td> const</td>
        </tr>
      </table>
  </td>
  <td class="mlabels-right">
<span class="mlabels"><span class="mlabel">inline</span></span>  </td>
  </tr>
</table>
</div><div class="memdoc">
<p>Compare the given hash with the stored one and test if they are equals </p><dl class="section return"><dt>Returns</dt><dd>if both hash are equals </dd></dl>

</div>
</div>
<a class="anchor" id="a649b8be8873d8550244a7656a98921e1"></a>
<div class="memitem">
<div class="memproto">
<div class="memtemplate">
template&lt;bool StoreHash&gt; </div>
<table class="mlabels">
  <tr>
  <td class="mlabels-left">
      <table class="memname">
        <tr>
          <td class="memname">TruncatedHash <a class="el" href="class_n_r_e_1_1_utility_1_1_bucket_entry_hash.php">NRE::Utility::BucketEntryHash</a>&lt; StoreHash &gt;::getTruncatedHash </td>
          <td>(</td>
          <td class="paramname"></td><td>)</td>
          <td> const</td>
        </tr>
      </table>
  </td>
  <td class="mlabels-right">
<span class="mlabels"><span class="mlabel">inline</span></span>  </td>
  </tr>
</table>
</div><div class="memdoc">
<dl class="section return"><dt>Returns</dt><dd>the truncated hash </dd></dl>

</div>
</div>
<a class="anchor" id="ac5fb7ad7eaffbd1b53fb77c49a8e2722"></a>
<div class="memitem">
<div class="memproto">
<div class="memtemplate">
template&lt;bool StoreHash&gt; </div>
<table class="mlabels">
  <tr>
  <td class="mlabels-left">
      <table class="memname">
        <tr>
          <td class="memname">void <a class="el" href="class_n_r_e_1_1_utility_1_1_bucket_entry_hash.php">NRE::Utility::BucketEntryHash</a>&lt; StoreHash &gt;::setHash </td>
          <td>(</td>
          <td class="paramtype">TruncatedHash&#160;</td>
          <td class="paramname"></td><td>)</td>
          <td></td>
        </tr>
      </table>
  </td>
  <td class="mlabels-right">
<span class="mlabels"><span class="mlabel">inline</span><span class="mlabel">protected</span></span>  </td>
  </tr>
</table>
</div><div class="memdoc">
<p>Set the internal stored hash </p>

</div>
</div>
<hr/>The documentation for this class was generated from the following file:<ul>
<li>/mnt/c/Users/abell/Documents/GitHub/NRE-Utility/src/Utility/HashTable/<a class="el" href="_n_r_e___hash_table_8hpp_source.php">NRE_HashTable.hpp</a></li>
</ul>
</div><!-- contents -->
<!-- HTML footer for doxygen 1.8.8-->
<!-- start footer part -->
</div>
</div>
</div>
</div>
</body>
</html>
