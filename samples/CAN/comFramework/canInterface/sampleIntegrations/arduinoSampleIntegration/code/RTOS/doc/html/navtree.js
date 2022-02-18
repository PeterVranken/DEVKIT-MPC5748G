var NAVTREE =
[
  [ "RTuinOS", "index.html", [
    [ "Software Documentation for RTuinOS", "index.html", null ],
    [ "Related Pages", "pages.html", [
      [ "Todo List", "todo.html", null ]
    ] ],
    [ "Data Structures", "annotated.html", [
      [ "dcf_timeInfo", "structdcf__time_info.html", null ],
      [ "dpy_display_t", "classdpy__display__t.html", null ]
    ] ],
    [ "Data Structure Index", "classes.html", null ],
    [ "Data Fields", "functions.html", null ],
    [ "File List", "files.html", [
      [ "adc_analogInput.cpp", "adc__analog_input_8cpp.html", null ],
      [ "adc_analogInput.h", "adc__analog_input_8h.html", null ],
      [ "aev_applEvents.h", "aev__appl_events_8h.html", null ],
      [ "but_button.cpp", "but__button_8cpp.html", null ],
      [ "but_button.h", "but__button_8h.html", null ],
      [ "clk_clock.cpp", "clk__clock_8cpp.html", null ],
      [ "clk_clock.h", "clk__clock_8h.html", null ],
      [ "dcf_taskDcf77.c", "dcf__task_dcf77_8c.html", null ],
      [ "dcf_taskDcf77.h", "dcf__task_dcf77_8h.html", null ],
      [ "dpy_display.cpp", "dpy__display_8cpp.html", null ],
      [ "dpy_display.h", "dpy__display_8h.html", null ],
      [ "gsl_systemLoad.c", "gsl__system_load_8c.html", null ],
      [ "gsl_systemLoad.h", "gsl__system_load_8h.html", null ],
      [ "rtos.c", "rtos_8c.html", null ],
      [ "rtos.config.h", "rtos_8config_8h.html", null ],
      [ "rtos.config.template.h", "rtos_8config_8template_8h.html", null ],
      [ "rtos.h", "rtos_8h.html", null ],
      [ "rtos_assert.h", "rtos__assert_8h.html", null ],
      [ "stdout.c", "stdout_8c.html", null ],
      [ "stdout.h", "stdout_8h.html", null ],
      [ "tc14_adcInput.cpp", "tc14__adc_input_8cpp.html", null ],
      [ "tc14_adcInput.h", "tc14__adc_input_8h.html", null ]
    ] ],
    [ "Directories", "dirs.html", [
      [ "code", "dir_62cc06e3d9750b025fdd8b597a181d85.html", [
        [ "applications", "dir_6be9a3711057ecfcb45b1ca9cf5a10b4.html", [
          [ "tc14_dcf", "dir_807dcae69f72fea6e9e26520b1b468d8.html", [
            [ "applCode", "dir_7a6495d70802eff2a02a56d0fb934246.html", null ],
            [ "rtosConfig", "dir_baa33b681d46f8d487cd115ec2b14c43.html", null ]
          ] ]
        ] ],
        [ "RTOS", "dir_13b87a902e0f43fef7b49a1470c6d5d0.html", null ]
      ] ]
    ] ],
    [ "Globals", "globals.html", null ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

