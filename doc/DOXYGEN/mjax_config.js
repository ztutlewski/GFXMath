MathJax.Hub.Config(
	{
		displayAlign: "left", 
		tex2jax: {inlineMath: [['%%','%%']]}
	});
	
MathJax.Hub.Queue(
    function () {
    var x = document.getElementsByTagName("body")[0];
	x.style.visibility = "";
    }
  );