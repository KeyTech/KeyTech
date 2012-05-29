package nl.keytech.reservation.spring;

import java.util.List;
import org.springframework.web.servlet.view.AbstractUrlBasedView;
import org.springframework.web.servlet.view.UrlBasedViewResolver;

public class JspTemplateViewResolver extends UrlBasedViewResolver {
	
	protected List<String> excludedTemplates;
	protected String templateJsp;

	public String getTemplateJsp() {
		return templateJsp;
	}

	public void setTemplateJsp(String templateJsp) {
		this.templateJsp = templateJsp;
	}

	public List<String> getExcludedTemplates() {
		return excludedTemplates;
	}

	public void setExcludedTemplates(List<String> excludedTemplates) {
		this.excludedTemplates = excludedTemplates;
	}

	@Override
	protected AbstractUrlBasedView buildView(String viewName) throws Exception {
		if(excludedTemplates.contains(viewName)) {
			return super.buildView(viewName);
		}
		
		JstlTemplateView view = (JstlTemplateView) super.buildView(templateJsp);
		view.setContentPage(getPrefix() + viewName + getSuffix());
		
		return view;
	}
}