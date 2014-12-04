<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
  version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns="http://www.w3.org/1999/xhtml">
 
  <xsl:output method="xml" indent="yes" encoding="UTF-8"/>
 
  <xsl:template match="/NumTest">
    <html lang="en">
      <head>
        <title>NumTest</title>
        <link href="css/bootstrap.min.css" rel="stylesheet"/>
      </head>
      <body>
        <xsl:call-template name="nav"/>
        <div class="container">
          <xsl:apply-templates select="testClass"/>
        </div>
        <script src="js/jquery.min.js"/>
        <script src="js/bootstrap.min.js"/>
      </body>
    </html>
  </xsl:template>

  <xsl:template name="nav">
    <nav class="navbar navbar-fixed-top" role="navigation">
      <div class="container-fluid">
        <div class="navbar-header"/>
        <div class="collapse navbar-collapse">
          <ul class="nav nav-stacked nav-pills bg-info">
            <xsl:apply-templates select="testClass" mode="nav"/>
          </ul>
        </div>
      </div>
    </nav>
  </xsl:template>

  <xsl:template match="testClass" mode="nav">
    <li>
      <a class="navbar-link">
        <xsl:attribute name="href">#<xsl:value-of select="name"/></xsl:attribute>
        [<xsl:value-of select="failedCount"/>]
        <xsl:value-of select="name"/>
      </a>
    </li>
  </xsl:template>
 
  <xsl:template match="testClass">
    <div>
      <xsl:attribute name="id">
        <xsl:value-of select="name"/>
      </xsl:attribute>
      <h2>
        <xsl:value-of select="name"/>
      </h2>
      <dl class="dl-horizontal">
        <dt>Failed</dt>
        <dd><xsl:value-of select="failedCount"/></dd>
        <dt>Max Residual</dt>
        <dd><xsl:value-of select="maxResidual"/></dd>
        <dt>eps</dt>
        <dd><xsl:value-of select="eps"/></dd>
      </dl>
      <span><xsl:value-of select="description"/></span>
      <table class="table table-striped table-condensed table-hover">
        <thead>
          <tr>
            <th>Index</th>
            <th>Type</th>
            <th>Result</th>
            <th>Residual</th>
            <th>N</th>
            <th>value</th>
            <th>answer</th>
          </tr>
        </thead>
        <tbody>
          <xsl:apply-templates select="test"/>
        </tbody>
      </table>
    </div>
  </xsl:template>

  <xsl:template match="test">
    <tr>
      <th><xsl:value-of select="index"/></th>
      <th><xsl:value-of select="type"/></th>
      <th><xsl:value-of select="result"/></th>
      <th><xsl:value-of select="residual"/></th>
      <th><xsl:value-of select="N"/></th>
      <th><xsl:value-of select="value"/></th>
      <th><xsl:value-of select="answer"/></th>
    </tr>
  </xsl:template>
 
</xsl:stylesheet>
