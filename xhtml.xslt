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
        <div class="container">
          <h1>NumTest</h1>
          <xsl:call-template name="summary"/>
          <xsl:apply-templates select="testClass"/>
        </div>
        <script src="js/jquery.min.js"/>
        <script src="js/bootstrap.min.js"/>
      </body>
    </html>
  </xsl:template>

  <xsl:template name="summary">
    <div>
      <h2>Summary</h2>
      <table class="table table-striped table-hover">
        <thead>
          <tr>
            <th>Name</th>
            <th>Failed Count</th>
            <th>Max Residual</th>
            <th>EPS</th>
          </tr>
        </thead>
        <tbody>
          <xsl:apply-templates select="testClass" mode="summary"/>
        </tbody>
      </table>
    </div>
  </xsl:template>

  <xsl:template match="testClass" mode="summary">
    <tr>
      <th>
        <a>
          <xsl:attribute name="href">#<xsl:value-of select="name"/></xsl:attribute>
          <xsl:value-of select="name"/>
        </a>
      </th>
      <th><xsl:value-of select="failedCount"/></th>
      <th><xsl:value-of select="maxResidual"/></th>
      <th><xsl:value-of select="eps"/></th>
    </tr>
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
