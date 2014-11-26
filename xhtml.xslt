<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
  version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns="http://www.w3.org/1999/xhtml">
 
  <xsl:output method="xml" indent="yes" encoding="UTF-8"/>
 
  <xsl:template match="/NumTest">
    <html>
      <head>
        <title>NumTest</title>
      </head>
      <body>
        <xsl:apply-templates select="testClass"/>
      </body>
    </html>
  </xsl:template>
 
  <xsl:template match="testClass">
    <div class="testClass">
      <h2>
        <xsl:value-of select="name"/>
      </h2>
      <span>
        <xsl:value-of select="description"/>
      </span>
      <table>
        <thead>
          <tr>
            <th>Index</th>
            <th>Type</th>
            <th>Result</th>
            <th>Residual</th>
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
    </tr>
  </xsl:template>
 
</xsl:stylesheet>
